#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define G 0.000005
#define MIN_DIST 1.0
const int unitSize = 8;//unitSize:每个计算单位的大小，多少个float
double wide = 1000;
double mass = 10;
double velo = 0.005;
int saveTimes = 0;

typedef struct Orb {
  double x,y,z,vx,vy,vz,m,st;
}Orb;
typedef union {
  Orb orbst;
  double fmem[8];
}UOrb;

void initList(Orb *olist, int nUnit, int style);
void calcOne(Orb*o, int oId, Orb*olist, int nUnit);
void calcGravity(Orb*o, Orb*ta, double dist, double*gx, double*gy, double*gz);
void printList(Orb *list, int len, int rank, const char* s);
void saveList(Orb *olist, int len, const char* filepath);
void loadList(double **list, int *len, const char* filepath);

int main(int argc, char *argv[])
{
    int rank, value=0, nWorkers;
    long nUnit = 5, nTimes = 3;
    int ch;
    while ((ch = getopt(argc, argv, "l:m:v:w:t:")) != -1) {
        switch (ch) {
            case 'l':
                nUnit = atoi(optarg);
                break;
            case 'm':
                mass = atof(optarg);
                break;
            case 'v':
                velo = atof(optarg);
                break;
            case 'w':
                wide = atof(optarg);
                break;
            case 't':
                nTimes = atoi(optarg);
                break;
            defualt:
                break;
        }
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nWorkers);
    int nUnitPerWorker = nUnit / nWorkers;//nUnit:list有多少个unit。list字节长度=sizeof(double)*unitSize
    int listSizeOfByte = sizeof(double) * unitSize * nUnit;
    int chunkSize = unitSize*nUnitPerWorker;
    Orb* list = (Orb*)malloc(listSizeOfByte);
    long calcTimes = (long)(nUnit) * (long)(nUnit) * (long)nTimes;
    printf("list addr=%p nUnit=%d nUnitPerWorker=%d chunkSize=%d listbytes=%d\n", list, nUnit, nUnitPerWorker, chunkSize, listSizeOfByte);
    printf("mass=%lf velo=%lf wide=%lf nTimes=%ld willTimes=%ld myUnits=[%ld,%ld]\n", mass, velo, wide, nTimes, calcTimes, rank*nUnitPerWorker, (rank+1)*nUnitPerWorker-1);

    // init list here
    if (rank == 0) {
        initList((Orb*)list, nUnit, 0);
        saveList(list, nUnit, "./thelist1");
    }
    // 广播必须每个rank都调用，否则报 Fatal error in PMPI_Barrier: Message truncated, error stack
    MPI_Bcast(list, nUnit*unitSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    //printList(list, nUnit, rank, "after init bcast");
    double startTime = MPI_Wtime(), endTime, usedTime;

    int i = 0, j = 0, k = 0;
    for (j=0; j<nTimes; ++j) {
        //list[rank*nUnitPerWorker].y += rank;//(double)rank*100+(double)j;

        for (k=0; k<nUnitPerWorker; ++k) {
            int oId = rank*nUnitPerWorker+k;
            Orb* o = list+oId;
            //printList(o, 1, rank, "now calc this:");
            calcOne(o, oId, list, nUnit);
        }
        //printf("list=%p list+i*chunkSize=%p chunkSize=%d\n", list, list+chunkSize, chunkSize);
/*
        if ((j+1) %10000 == 0) {
            //usleep(100000);
            if (rank == 0) {
                saveList(list, nUnit, "./thelist1");
            }
        }
*/
        // bcast 对于发送方来说等于send，对于接受方来说等于recv，调用时需要for i in nWorkers来依次bcast。相当于调用nWorkers*nWorkers次。
        // 不加for循环，root设置为自己，相当于只有root.send,没有other.recv。
        for (i=0; i<nWorkers; ++i) MPI_Bcast(((double*)list)+i*chunkSize, chunkSize, MPI_DOUBLE, i, MPI_COMM_WORLD);
        //MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    //printList(list, nUnit, rank, "finally");

    endTime = MPI_Wtime();
    usedTime = endTime - startTime;
    printf("all time:%f calc times:%ld cps:%g bps=%g sps=%g save times:%d\n", usedTime, calcTimes, (double)calcTimes/(usedTime), (double)nTimes/(usedTime), (double)saveTimes/usedTime, saveTimes);
    saveList(list, nUnit, "./thelist1");
    free(list);
    list = NULL;
    MPI_Finalize();
    return 0;
}

void printList(Orb *list, int len, int rank, const char* s) {
    int bufferlen = 1000000;
    static char* str = NULL;
    if (str == NULL) {
        str = (char*) malloc(bufferlen);//
    } else {
        memset(str, 0, bufferlen);
    }
    int i = 0, pos = 0;
    for (i=0; i<len; i++) {
        Orb* o = list + i;
        char stmp[255] = {};
        sprintf(stmp, "%f,%f,%f,%f,%f,%f,%f,%.2f\n", o->x,o->y,o->z,o->vx,o->vy,o->vz,o->m,o->st);
        memcpy((str+pos), stmp, strlen((const char*)stmp));
        pos += strlen(stmp);
        if (pos>=bufferlen) {
            printf("str not enough! i=%d/len=%d rank=%d\n", i, len, rank);
            break;
        }
    }
    printf("%s, rank=%d list={\n%s}\n", s, rank, str);
}
/*模拟输出到json,似乎精度有损失*/
void saveList(Orb *olist, int len, const char* filepath) {
    FILE * f = fopen(filepath, "w");
    if (f == NULL) {
        printf("cannot save to file:%s", filepath);
        return;
    }
    ++saveTimes;
    fprintf(f, "[");
    int i = 0;
    for (i=0; i<len; i++) {
        Orb* o = olist + i;
        //char stmp[255] = {};
        fprintf(f, "{\"x\":%g,\"y\":%g,\"z\":%g,\"vx\":%g,\"vy\":%g,\"vz\":%g,\"m\":%lf,\"st\":%d,\"id\":%d},", o->x,o->y,o->z,o->vx,o->vy,o->vz,o->m,(o->st<0?1:2),i);
    }
    fseek(f, -1, SEEK_CUR);
    fprintf(f, "]");
    fclose(f);
}
/**/
void loadList(double **list, int *len, const char* filepath) {
}
void initList(Orb *olist, int nUnit, int style) {
    int i = 0;
    srandom(time(NULL));
    for (i=0; i<nUnit; ++i) {
        //Orb* o = (Orb*)(list+i*unitSize);
        Orb* o = olist+i;
        o->x  = (double)random()/(double)RAND_MAX*wide - wide/2.0;
        o->y  = (double)random()/(double)RAND_MAX*wide - wide/2.0;
        o->z  = (double)random()/(double)RAND_MAX*wide - wide/2.0;
        o->vx = (double)random()/(double)RAND_MAX*velo - velo/2.0;
        o->vy = (double)random()/(double)RAND_MAX*velo - velo/2.0;
        o->vz = (double)random()/(double)RAND_MAX*velo - velo/2.0;
        o->m  = (double)random()/(double)RAND_MAX*mass;
        o->st = -(double)i;
    }
}
void calcGravity(Orb*o, Orb*ta, double dist, double*gx, double*gy, double*gz) {
    double a = ta->m / (dist*dist) * G;
    *gx += - a * (o->x - ta->x) / dist;
    *gy += - a * (o->y - ta->y) / dist;
    *gz += - a * (o->z - ta->z) / dist;
}
/* Orb update once with list */
void calcOne(Orb*o, int oId, Orb*olist, int nUnit) {
    //if (o->st < 0) {
        int i = 0, isTooRappid = 0;
        double gax = 0, gay = 0, gaz = 0, dist = 0;
        for (i=0; i<nUnit; ++i) {
            Orb* ta = olist+i;
            if (o->st < 0 && ta->st < 0 && oId != i) {
                dist = sqrt(((ta->x-o->x)*(ta->x-o->x)+(ta->y-o->y)*(ta->y-o->y)+(ta->z-o->z)*(ta->z-o->z)));
                isTooRappid = dist*dist<(o->vx*o->vx+o->vy*o->vy+o->vz*o->vz)*10;
                if (dist<MIN_DIST || isTooRappid) {
                    // crash
                    if (o->m < ta->m) {
                        o->st = -o->st;
                        printf("one crash: oid=%d, tid=%d dist=%f isTooRappid=%d\n", oId, i, dist, isTooRappid);
                    }
                    continue;
                }
                calcGravity(o, ta, dist, &gax, &gay, &gaz);
            }
        }
        o->x += o->vx;
        o->y += o->vy;
        o->z += o->vz;
        o->vx += gax;
        o->vy += gay;
        o->vz += gaz;
    //}
}


