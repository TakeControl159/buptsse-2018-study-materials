
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "math_constants.h"
#include "math_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct Orb {
	double x;
	double y;
	double z;
	double vx;
	double vy;
	double vz;
	double m;
	double st;
}Orb;

#define G 0.000005
#define MIN_DIST 1.0
const int unitSize = 8;//unitSize:size of each unit:8 floats
double wide = 10000;
double mass = 10;
double velo = 0.005;
int saveTimes = 0;
int calcTimes = 1000;

int nUnit = 100;
int nTimes = 1000;
int nBlock = 1;
int nThread = 1;
const char* saveFile = "thelist1";


cudaError_t calcOrbsWithCuda(Orb* olist, int nUnit, int nTimes, const char* saveFile);

//__global__ void calcOne(Orb*o, int oId, Orb*olist, int nUnit);
__global__ void calcOneInDevice(void *polist, int nUnit);
Orb* newOrbList(int nUnit, int style);
void deleteOrbList(Orb *olist);
void initOrbList(Orb *olist, int nUnit, int style);
void printList(Orb* olist, int nNum);
void saveList(Orb* olist, int nNum, const char* saveFile);

__global__ void calcOneInDevice(void *polist, int nUnit)
{
	int tid = threadIdx.x*gridDim.x + blockIdx.x;
	//threadIdx.x will be 0 to nThread, you should plus as oid manual
	//printf("this is thread:%d,%d,%d grid:%d,%d,%d blockIdx:%d,%d,%d nUnit=%d tid=%d\n", threadIdx.x, threadIdx.y, threadIdx.z, gridDim.x, gridDim.y, gridDim.z, blockIdx.x, blockIdx.y, blockDim.z, nUnit, tid);

	if (tid >= nUnit) {
		return;
	}

	Orb* olist = (Orb*)polist;
	Orb* o = olist + tid;
	int oId = tid;
	//if (o->st < 0) {
	int i = 0, isTooRappid = 0;
	double gax = 0, gay = 0, gaz = 0, dist = 0;
	//printf("o[%d]={%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf}\n", tid, (o)->x, (o)->y, (o)->z, (o)->vx, (o)->vy, (o)->vz, (o)->m, (o)->st);
	
	for (i = 0; i<nUnit; ++i) {
		Orb* ta = olist + i;
		//printf("ta[%d][%d]={%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf}\n", tid, i, (ta)->x, (ta)->y, (ta)->z, (ta)->vx, (ta)->vy, (ta)->vz, (ta)->m, (ta)->st);

		if (o->st < 0 && ta->st < 0 && oId != i) {
			dist = sqrt(((ta->x - o->x)*(ta->x - o->x) + (ta->y - o->y)*(ta->y - o->y) + (ta->z - o->z)*(ta->z - o->z)));
			isTooRappid = dist*dist<(o->vx*o->vx + o->vy*o->vy + o->vz*o->vz) * 10;
			if (dist<MIN_DIST || isTooRappid) {
				// crash
				if (o->m < ta->m) {
					o->st = -o->st;
					printf("one crash: oid=%d, tid=%d dist=%f isTooRappid=%d\n", oId, i, dist, isTooRappid);
				}
				continue;
			}
			//calcGravity<<<1,1>>>(o, ta, dist, &gax, &gay, &gaz);

			double a = ta->m / (dist*dist) * G;
			gax += -a * (o->x - ta->x) / dist;
			gay += -a * (o->y - ta->y) / dist;
			gaz += -a * (o->z - ta->z) / dist;
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

Orb* newOrbList(int nUnit, int style) {

	int listSizeOfByte = sizeof(double) * unitSize * nUnit;
	Orb* list = (Orb*)malloc(listSizeOfByte);
	initOrbList(list, nUnit, style);
	return list;
}

void deleteOrbList(Orb *olist) {
	if (olist != NULL) {
		delete(olist);
	}
}
void initOrbList(Orb *olist, int nUnit, int style) {
	int i = 0;
	srand(time(NULL));
	for (i = 0; i<nUnit; ++i) {
		//Orb* o = (Orb*)(list+i*unitSize);
		Orb* o = olist + i;
		o->x = (double)rand() / (double)RAND_MAX*wide - wide / 2.0;
		o->y = (double)rand() / (double)RAND_MAX*wide - wide / 2.0;
		o->z = (double)rand() / (double)RAND_MAX*wide - wide / 2.0;
		o->vx = (double)rand() / (double)RAND_MAX*velo - velo / 2.0;
		o->vy = (double)rand() / (double)RAND_MAX*velo - velo / 2.0;
		o->vz = (double)rand() / (double)RAND_MAX*velo - velo / 2.0;
		o->m = (double)rand() / (double)RAND_MAX*mass;
		o->st = -(double)i;
	}
}

int getArgInt(const int argc, const char** argv, const char* flag, int defaultValue) {
	int value = defaultValue;
	for (int i = 0; i < argc; i++) {
		if (0 == strcmp(flag, argv[i]) && i<argc-1) {
			sscanf(argv[i + 1], "%d", &value);
			break;
		}
	}
	return value;
}
const char* getArgStr(const int argc, const char** argv, const char* flag, const char* defaultValue) {
	const char* value = defaultValue;
	for (int i = 0; i < argc; i++) {
		if (0 == strcmp(flag, argv[i]) && i<argc - 1) {
			value = argv[i + 1];
			break;
		}
	}
	return value;
}

int main(int argc, const char**argv)
{
nUnit = getArgInt(argc, argv, "-n", nUnit);
nTimes = getArgInt(argc, argv, "-t", nTimes);
nBlock = getArgInt(argc, argv, "-b", nBlock);
nThread = getArgInt(argc, argv, "--thread", nThread);
saveFile = getArgStr(argc, argv, "--savefile", "thelist1");

printf("nUnit=%d, nTimes=%d nBlock=%d nThread=%d savefile=%s\n", nUnit, nTimes, nBlock, nThread, saveFile);

cudaError_t cudaStatus;
Orb* olist = newOrbList(nUnit, 1);

printList(olist, nUnit);

cudaStatus = calcOrbsWithCuda(olist, nUnit, nTimes, saveFile);
if (cudaStatus != cudaSuccess) {
	fprintf(stderr, "calcOrbsWithCuda failed!");
	return 1;
}



// cudaDeviceReset must be called before exiting in order for profiling and
// tracing tools such as Nsight and Visual Profiler to show complete traces.
cudaStatus = cudaDeviceReset();
if (cudaStatus != cudaSuccess) {
	fprintf(stderr, "cudaDeviceReset failed!");
	return 1;
}

printf("calc done-------------------\n");
printList(olist, nUnit);

saveList(olist, nUnit, saveFile);
printf("save ok %s -------------------\n", saveFile);

deleteOrbList(olist);
scanf("%d", &nUnit);


return 0;
}

cudaError_t calcOrbsWithCuda(Orb* olist, int nUnit, int nTimes, const char* saveFile) {
	Orb* dev_a = 0;
	//int* dev_b = 0;
	cudaError_t cudaStatus;

	// Choose which GPU to run on, change this on a multi-GPU system.
	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
		goto Error;
	}

	// Allocate GPU buffers for three vectors (two input, one output)    .
	cudaStatus = cudaMalloc((void**)&dev_a, nUnit * sizeof(Orb));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMalloc failed!");
		goto Error;
	}

	// Copy output vector from GPU buffer to host memory.
	cudaStatus = cudaMemcpy(dev_a, (void*)olist, nUnit * sizeof(Orb), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpyHostToDevice failed!");
		goto Error;
	}

	for (int i = 0; i < nTimes; ++i) {

		// do
		calcOneInDevice << <nBlock, nThread>> >(dev_a, nUnit);

		// Check for any errors launching the kernel
		cudaStatus = cudaGetLastError();
		if (cudaStatus != cudaSuccess) {
			fprintf(stderr, "calcOneInDevice launch failed: %s\n", cudaGetErrorString(cudaStatus));
			goto Error;
		}

		// cudaDeviceSynchronize waits for the kernel to finish, and returns
		// any errors encountered during the launch.
		// code 30: you should change or disable WDDM TDR delay in NVIDIA Nsight Monitor, Options
		cudaStatus = cudaDeviceSynchronize();
		if (cudaStatus != cudaSuccess) {
			fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching calcOneInDevice!\n", cudaStatus);
			goto Error;
		}

		if (i*nUnit*nUnit > 10000) {
			cudaMemcpy((void*)olist, dev_a, nUnit * sizeof(Orb), cudaMemcpyDeviceToHost);
			saveList(olist, nUnit, saveFile);
		}
	}

	// Copy output vector from GPU buffer to host memory.
	cudaStatus = cudaMemcpy((void*)olist, dev_a, nUnit * sizeof(Orb), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpyDeviceToHost failed!");
		goto Error;
	}

Error:
	cudaFree(dev_a);
	//cudaFree(dev_b);

	return cudaStatus;
}


void printList(Orb* olist, int nNum) {
	for (int i = 0; i < nNum; i++) {
		printf("{%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf}\n", (olist + i)->x, (olist + i)->y, (olist + i)->z, (olist + i)->vx, (olist + i)->vy, (olist + i)->vz, (olist + i)->m, (olist + i)->st);
	}
}

void saveList(Orb* olist, int nNum, const char* saveFile) {
	if (saveFile != NULL) {
		FILE* fhandle = fopen(saveFile, "w");

		if (olist != NULL) {
			fprintf(fhandle, "[");
			for (int i = 0; i < nNum; i++) {
				fprintf(fhandle, "{%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf},", (olist + i)->x, (olist + i)->y, (olist + i)->z, (olist + i)->vx, (olist + i)->vy, (olist + i)->vz, (olist + i)->m, (olist + i)->st);
			}
			fseek(fhandle, -1, SEEK_CUR);
			fprintf(fhandle, "]");
		}

		fclose(fhandle);
	}
}