#pragma once
#define F_NUM 7
#define G 6.67e-11
#include <math.h>
#include <stdlib.h>

class Node;
class Vector {
public:
	double x = 0;
	double y = 0;
	Vector operator+(const Vector &other) {
		Vector vector;
		vector.x = this->x + other.x;
		vector.y = this->y + other.y;
		return vector;
	}
	void operator+=(const Vector &other) {
		this->x += other.x;
		this->y += other.y;
	}
	Vector operator*(double scalar) {
		Vector vector;
		vector.x = this->x * scalar;
		vector.y = this->y * scalar;
		return vector;
	}
	double distance(const Vector &other) {
		return pow((this->x - other.x), 2) + pow((this->y - other.y), 2);
	}
};

struct Point {
	double m;
	Vector v;
	Vector p;
	double r;
};

Vector getCenter(double **points, int count);
Vector getCenter(Node **points, int count);

class Node {
public:
	int id = -1;
	bool isLeaf = true;
	Point value;
	Node *parent = nullptr;
	Node *child[4] = { nullptr };

	void getLeaves(Node **result, int *ptr) {
		if (isLeaf) {
			result[(*ptr)++] = this;
		}
		for (int i = 0; i < 4; ++i) {
			if (child[i] != nullptr)
				child[i]->getLeaves(result, ptr);
		}
	}

	void getForce(Vector *f) {
		if (parent == nullptr) return;
		for (int i = 0; i < 4; ++i) {
			Node *sibling = parent->child[i];
			if (sibling == this || sibling == nullptr) continue;
			Vector bf;
			double m1 = this->value.m, m2 = sibling->value.m;
			double dx = sibling->value.p.x - this->value.p.x, dy = sibling->value.p.y - this->value.p.y;
			double r2 = pow(dx, 2) + pow(dy, 2);
			double minR = this->value.r + sibling->value.r;
			if (r2 < minR * minR) {
				r2 = minR * minR;
			}
			double ft = G * m1 * m2 / r2;
			double fx = ft * dx / sqrt(r2), fy = ft * dy / sqrt(r2);
			bf.x = fx, bf.y = fy;
			*f += bf;
		}
		parent->getForce(f);
	}

	void move(double t) {
		if (!isLeaf) return;
		double m = this->value.m;
		Vector v0 = this->value.v, F;
		getForce(&F);
		Vector a = F * (1.0 / m);
		double dx = v0.x * t + 0.5 * a.x * t * t;
		double dy = v0.y * t + 0.5 * a.y * t * t;
		this->value.p.x += dx;
		this->value.p.y += dy;
		this->value.v += a;
	}

	void update() {
		double newM = 0;
		Vector newP, newV;
		for (int i = 0; i < 4; ++i) {
			if (this->child[i] != nullptr) {
				this->child[i]->update();
				newM += this->child[i]->value.m;
				newP += this->child[i]->value.p;
				newV += this->child[i]->value.v;
			}
		}
		if (!this->isLeaf) {
			this->value.m = newM;
			this->value.p = newP;
			this->value.v = newV;
		}
	}

	void build(Node **nodes, int count) {
		Node **parts[4];
		int ptrs[4] = { 0 };

		Vector center = getCenter(nodes, count);
		this->value.p = center;

		for (int i = 0; i < 4; ++i) {
			parts[i] = (Node**)malloc(sizeof(Node) * (count / 4 + 3));
		}
		double mTotal = 0, vxTotal = 0, vyTotal = 0;
		for (int i = 0; i < count; ++i) {
			double x = nodes[i]->value.p.x, y = nodes[i]->value.p.y;
			mTotal += nodes[i]->value.m;
			vxTotal += nodes[i]->value.v.x;
			vyTotal += nodes[i]->value.v.y;
			if (x > center.x) {
				if (y > center.y) {
					parts[3][ptrs[3]++] = nodes[i];
				}
				else {
					parts[1][ptrs[1]++] = nodes[i];
				}
			}
			else {
				if (y > center.y) {
					parts[2][ptrs[2]++] = nodes[i];
				}
				else {
					parts[0][ptrs[0]++] = nodes[i];
				}
			}
		}

		this->value.m = mTotal;
		this->value.v.x = vxTotal;
		this->value.v.y = vyTotal;

		if (count <= 1) return;

		for (int i = 0; i < 4; ++i) {
			if (ptrs[i] > 0) {
				this->isLeaf = false;
				if (count == 1) child[i] = nodes[0];
				else child[i] = new Node;
				child[i]->parent = this;
				child[i]->build(parts[i], ptrs[i]);
			}
			free(parts[i]);
		}
	}

	void build(double **points, int count) {
		double **parts[4];
		int ptrs[4] = { 0 };

		Vector center = getCenter(points, count);
		this->value.p = center;

		for (int i = 0; i < 4; ++i) {
			parts[i] = (double**)malloc((count / 4 + 3) * sizeof(double) * F_NUM);
		}
		double mTotal = 0, vxTotal = 0, vyTotal = 0;
		for (int i = 0; i < count; ++i) {
			double x = points[i][4], y = points[i][5];
			mTotal += points[i][1];
			vxTotal += points[i][2];
			vyTotal += points[i][3];
			if (x > center.x) {
				if (y > center.y) {
					parts[3][ptrs[3]++] = points[i];
				}
				else {
					parts[1][ptrs[1]++] = points[i];
				}
			}
			else {
				if (y > center.y) {
					parts[2][ptrs[2]++] = points[i];
				}
				else {
					parts[0][ptrs[0]++] = points[i];
				}
			}
		}

		this->value.m = mTotal;
		this->value.v.x = vxTotal;
		this->value.v.y = vyTotal;

		if (count == 1) {
			this->id = points[0][0];
			this->value.r = points[0][6];
		}
		if (count <= 1) return;

		for (int i = 0; i < 4; ++i) {
			if (ptrs[i] > 0) {
				this->isLeaf = false;
				child[i] = new Node;
				child[i]->parent = this;
				child[i]->build(parts[i], ptrs[i]);
			}
			free(parts[i]);
		}
	}
};


Vector getCenter(double **points, int count) {
	double xTotal = 0, yTotal = 0;
	for (int i = 0; i < count; i++) {
		xTotal += points[i][4];
		yTotal += points[i][5];
	}
	xTotal /= count;
	yTotal /= count;
	Vector center;
	center.x = xTotal;
	center.y = yTotal;
	return center;
}

Vector getCenter(Node **nodes, int count) {
	double xTotal = 0, yTotal = 0;
	for (int i = 0; i < count; i++) {
		xTotal += nodes[i]->value.p.x;
		yTotal += nodes[i]->value.p.y;
	}
	xTotal /= count;
	yTotal /= count;
	Vector center;
	center.x = xTotal;
	center.y = yTotal;
	return center;
}