#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>
#include<graphics.h>


// 定义星球结构体
struct Star
{
	double cox, coy;  // 坐标
	double weight;    // 重量
};

// 星球状态结构体
// 存放星球受力方向和原来的方向
struct StarStates
{
	double pre_x, pre_y;
	double Fx, Fy;
};

// 处理器信息
struct ProcessorInfo
{
	MPI_Comm MPIcomm;
	MPI_Datatype MPItype;
	MPI_Request requests[2];
	Star* starBuf1, * starBuf2, * StarBuf3;
	int stage, lastStage, maxLength;
	int left, right;
	int typeSize;
};

void ProcessorCreate(MPI_Comm MPIcomm, MPI_Datatype type, int maxsize, void** Info)
{
	ProcessorInfo* processorBuf = (ProcessorInfo*)malloc(sizeof(ProcessorInfo));
	MPI_Aint dextent;
	int trues = 1, size, dsize, maxbuf;

	// 开始创建多个进程计算
	MPI_Comm_size(MPIcomm, &size);
	MPI_Cart_create(MPIcomm, 1, &size, &trues, 1, &processorBuf->MPIcomm);
	MPI_Cart_shift(processorBuf->MPIcomm, 0, 1, &processorBuf->left, &processorBuf->right);

	MPI_Type_size(type, &dsize);
	MPI_Type_extent(type, &dextent);
	if (2 * dsize <= int(dextent))
	{
		fprintf(stderr, "数据类型必须是连续的:大小为 = %d and 范围为 = %d\n",
			dsize, dextent);
		free(processorBuf);
		*Info = 0;
		return;
	}

	processorBuf->typeSize = dextent;
	MPI_Allreduce(&maxsize, &maxbuf, 1, MPI_INT, MPI_MAX, MPIcomm);
	processorBuf->maxLength = maxbuf;
	processorBuf->StarBuf3 = (Star*)malloc(2 * maxbuf);
	processorBuf->starBuf1 = processorBuf->StarBuf3;
	processorBuf->starBuf2 = (Star*)((char*)processorBuf->starBuf1 + maxbuf);
	processorBuf->MPItype = type;
	processorBuf->stage = 0;
	processorBuf->lastStage = size - 1;
	*Info = (void*)processorBuf;
}

void ProcessorStart(void* Info, void* mybuf, int len, int qcopy)
{
	ProcessorInfo* p = (ProcessorInfo*)Info;
	if (p->stage != 0)
	{
		fprintf(stderr, "Can only start pipe weht\n");
		return;
	}
	if (p->lastStage == 0)
	{
		return;
	}
	MPI_Irecv(p->starBuf1, p->maxLength, p->MPItype, p->left,
		0, p->MPIcomm, &p->requests[0]);
	if (qcopy)
	{
		memcpy(p->starBuf2, mybuf, len * p->typeSize);
		mybuf = p -> starBuf2;
	}
	MPI_Isend(mybuf, len, p->MPItype, p->right, 0, p->MPIcomm, &p->requests[1]);
}

void ProcessorPush(void* Info, Star** recvbuf, int* recvlen)
{
	ProcessorInfo* p = (ProcessorInfo*)Info;
	MPI_Status statuses[2];
	Star* tmp;
	if (++p->lastStage == 0)
		return;
	MPI_Waitall(2, p->requests, statuses);
	MPI_Get_count(&statuses[0], p->MPItype, recvlen);
	*recvbuf = p->starBuf1;
	if (++p->stage == p->lastStage)
	{
		p->stage = 0;
		return;
	}

	// 开始循环
	tmp = p->starBuf1;
	p->starBuf1 = p->starBuf2;
	p->starBuf2 = tmp;
	MPI_Irecv(p->starBuf1, p->maxLength, p->MPItype, p->left, 0,
		p->MPIcomm, &p->requests[1]);
}

void MPE_Pipe_free(void** Info)
{
	ProcessorInfo* p = (ProcessorInfo*)*Info;
	if (p->stage != 0)
	{
		fprintf(stderr, "处理器不能被释放，%d个阶段后才能释放\n",
			p->lastStage - p->stage);
		return;
	}
	MPI_Comm_free(&p->MPIcomm);
	free(p->StarBuf3);
	*Info = 0;
}

void computeForces(Star* Stars, StarStates* ss, int npart, Star* recvbuf, int rlen, double* max_f)
{
	int i, j;
	double cur_x, yi, mi, rx, ry, mj, r, fx, fy;
	double xnew, ynew, rmin;
	//计算受力
	for (i = 0; i < npart; i++)
	{
		rmin = 100.0;
		cur_x = Stars[i].cox;
		yi = Stars[i].coy;
		fx = 0.0;
		fy = 0.0;
		for ( j = 0; j < rlen; j++)
		{
			//计算距离
			rx = cur_x - recvbuf[j].cox;
			ry = yi - recvbuf[j].coy;
			mj = recvbuf[j].weight;
			r = rx * rx + ry * ry;
			if (r == 0.0)
				continue;
			if (r < rmin)
				rmin = r;
			r = r * sqrt(r);

			//计算受力
			fx += mj * rx / r;
			fy += mj * ry / r;
		}
		//受力累计
		ss[i].Fx -= fx;
		ss[i].Fy -= fy;
		fx = sqrt(fx * fx + fy * fy) / rmin;
		if (fx > * max_f) *max_f = fx;
	}
}

// 图形界面显示
void PrintParticles(Star* Stars, Star* Star, int npart, double t)
{
	for (int i = 0; i < npart; i++)
	{
		double ball_x = 400, ball_y = 100;
		setcolor(BLACK);
		setfillcolor(BLACK); //黑色背景
		fillcircle(ball_x + Star[i].cox * 10, ball_y + Star[i].coy * 10, 2);
		setcolor(BLACK);
		setfillcolor(YELLOW); //黄色星球
		fillcircle(ball_x + Stars[i].cox * 15, ball_y + Stars[i].coy + 10, 2);
	}
}

int main(int argc, char** argv)
{
	// 随机数种子
	srand((unsigned)time(NULL));
	Star Stars[5000], temStars[5000];
	StarStates ss[5000];
	Star* recvbuf;

	int rank, size, npart, i, j;
	int step, rlen;
	int totpart, cnt;
	MPI_Datatype particletype;
	double time;
	double dt, pre_dt;
	double t;
	double a0, a1, a2;
	void* info;
	int debug_flag = 1;

	// 初始化图形面板0
	initgraph(500, 500);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	npart = 50 * size;
	printf("%d", size);
	if (argc > 1)
		npart = atoi(argv[1]) / size;
	if (npart > 400)
		MPI_Abort(MPI_COMM_WORLD, 1);

	MPI_Allreduce(&npart, &totpart, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	cnt = 100000;
	// 创建一个连续的数据类型并提交
	MPI_Type_contiguous(4, MPI_DOUBLE, &particletype);  
	MPI_Type_commit(&particletype);

	for (int i = 0; i < npart; i++)
	{
		Stars[i].cox = rand() % 500;
		Stars[i].coy = rand() % 500;

		Stars[i].weight = 0.5;

		ss[i].pre_x = Stars[i].cox;
		ss[i].pre_y = Stars[i].coy;
	}

	dt = 0.001;
	pre_dt = 0.001;

	ProcessorCreate(MPI_COMM_WORLD, particletype, npart, &info);
	time = MPI_Wtime();
	t = 0.0;

	while (cnt--)
	{
		double max_f, dt_est, new_dt, dt_new;

		// 加载初始化的缓冲区。
		ProcessorStart(info, Stars, npart, 1);
		// 计算加速度
		a0 = 2.0 / (dt * (dt + pre_dt));
		a2 = 2.0 / (pre_dt * (dt + pre_dt));
		a1 = -(a0 + a2);

		//计算受力
		max_f = 0;
		computeForces(Stars, ss, npart, Stars, npart, &max_f);

		// 计算相互作用力
		for (step = 0; step < size; step++)
		{
			// 创建树，计算受力
			ProcessorPush(info, &recvbuf, &rlen);
			computeForces(Stars, ss, npart, recvbuf, rlen, &max_f);
		}

		for (int i = 0; i < npart; i++)
		{
			temStars[i].cox = Stars[i].cox;
			temStars[i].coy = Stars[i].coy;
		}

		Sleep(1000);
		// 更新星球位置
		for (int i = 0; i < npart; i++)
		{
			double xi, yi;
			xi = Stars[i].cox;
			yi = Stars[i].coy;

			Stars[i].cox = (ss[i].Fx - a1 * xi - a2 * ss[i].pre_x) / a0;
			Stars[i].coy = (ss[i].Fy - a1 * yi - a2 * ss[i].pre_y) / a0;

			ss[i].pre_x = xi;
			ss[i].pre_y = yi;
			ss[i].Fx = 0;
			ss[i].Fy = 0;
		}
		t + dt;

		// 绘画星球点
		if (debug_flag && rank == 0)
			PrintParticles(Stars, temStars, npart, t);

		dt_est = 1.0 / sqrt(max_f);
		if (dt_est < 1.0e-6) dt_est = 1.0e-6;
		MPI_Allreduce(&dt_est, &dt_new, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);

		// 重新计算时间评估
		if (dt_new < dt)
		{
			pre_dt = dt;
			dt = dt_new;
			if (debug_flag && rank == 0)
				printf("new time step is %f\n", dt);
		}

		else if (dt_new > 4.0 * dt)
		{
			pre_dt = dt;
			dt *= 2.0;
			if (debug_flag && rank == 0)
				printf("new time step is %f\n", dt);
		}
	}

	time = MPI_Wtime() - time;
	if (rank == 0) {
		printf("计算" %d个星体在%fs内\n", totpart, time);
	}

	MPE_Pipe_free(&info);
	MPI_Type_free(&particletype);
	MPI_Finalize();
	system("pause");
	return 0;
}