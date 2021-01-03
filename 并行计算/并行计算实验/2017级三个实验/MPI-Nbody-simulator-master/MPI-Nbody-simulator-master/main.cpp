#include "mpi.h"
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
#include "quard.h"

#define _CRT_SECURE_NO_WARNINGS
#define SPEED 10
#define PI 3.1415926535898
#define WIDTH 500
#define HEIGHT 500

double** getPoints(int);
double** getPoints(int count) {
	double** a = (double**)malloc(sizeof(double) * F_NUM * count);
	srand(time(0));
	for (int i = 0; i < count; ++i) {
		double* temp = (double*)malloc(sizeof(double) * F_NUM);
		temp[0] = i;
		temp[1] = (double)rand() / RAND_MAX * 10e+8 + 10e+4;
		temp[2] = 0;
		temp[3] = 0;
		temp[4] = (double)rand() / RAND_MAX * WIDTH * 10 - WIDTH * 5;
		temp[5] = (double)rand() / RAND_MAX * HEIGHT * 10 - HEIGHT * 5;
		temp[6] = (double)rand() / RAND_MAX;
		a[i] = temp;
	}
	return a;
}

// 将total分成count份
int* split(int total, int count) {
	int *result = (int*)malloc(sizeof(int) * count);
	int i;
	for (i = 0; i < count; ++i) {
		result[i] = total / count;
	}
	result[i - 1] = total / count + total % count;
	return result;
}

void loop(Node **trees, int *counts, int numprocs, int myid, void(*callback)(Node**, int)) {
	Node *tree = trees[myid];
	// 获取叶结点
	Node **leaves = (Node**)malloc(sizeof(Node) * counts[myid]);
	int ptr = 0;
	tree->getLeaves(leaves, &ptr);
	for (int i = 0; i < counts[myid]; i++) {
		leaves[i]->move(SPEED);
	}
	tree->update();
	if (myid == numprocs - 1 && numprocs - 1 != 0) {
		char flag = 1;
		MPI_Send(&flag, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}

	if (myid == 0) {
		if (numprocs - 1 != 0) {
			MPI_Status status;
			char flag = 0;
			MPI_Recv(&flag, 1, MPI_CHAR, numprocs - 1, 0, MPI_COMM_WORLD, &status);
		}
		Node *upTree = new Node;
		upTree->build(trees, numprocs);
		Node **upLeaves = (Node**)malloc(sizeof(Node) * numprocs);
		int ptr = 0;
		upTree->getLeaves(upLeaves, &ptr);
		for (int i = 0; i < numprocs; ++i) {
			upLeaves[i]->move(SPEED);
		}
		upTree->update();
		free(upLeaves);
	}
	callback(leaves, counts[myid]);
}

void algoCallback(Node** leaves, int count) {
	glutReshapeWindow(WIDTH, HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glColor3f(1, 1, 0);
	for (int i = 0; i < count; ++i) {
		Vector p = leaves[i]->value.p;
		glRectd(p.x / WIDTH * 2, p.y / HEIGHT * 2, p.x / WIDTH * 2 + 5.0 / WIDTH, p.y / HEIGHT * 2 + 5.0 / HEIGHT);
	}
	free(leaves);
	glPopMatrix();
	glutSwapBuffers();

}

void algo() {
	static int flag = 0;
	static Node **trees;
	static int *counts;
	static int numprocs, myid;
	if (!flag) {
		int namelen;
		char processor_name[MPI_MAX_PROCESSOR_NAME];
		MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
		MPI_Comm_rank(MPI_COMM_WORLD, &myid);
		MPI_Get_processor_name(processor_name, &namelen);

		// point: [id, 质量, 速度x, 速度y, x, y, 半径]
		const int count = 10000;
		trees = (Node**)malloc(sizeof(Node) * numprocs);

		// 将1w个点分给多个进程
		counts = split(count, numprocs);
		if (myid == 0) {
			for (int i = 0; i < numprocs; ++i) {
				Node *tree;
				double **points = getPoints(counts[i]);
				// 将天体建成四叉树
				tree = new Node;
				tree->build(points, counts[i]);
				trees[i] = tree;
			}
		}
		flag = 1;
	}
	loop(trees, counts, numprocs, myid, algoCallback);
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(1, 1);
	glutInitWindowSize(HEIGHT, WIDTH);
	glViewport(0, 0, 1, 1);
	glutCreateWindow("天体运行问题");
	glutDisplayFunc(algo);
	glutMainLoop();
	return 0;
}