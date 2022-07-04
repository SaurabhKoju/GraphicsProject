#pragma once
#include "GMath.h"
#include <vector>

struct triangle {
	Vector<4> p1, p2, p3, p4;
};

struct mesh {
	std::vector<triangle> triangles;
};

Vector<2> get2d(Vector<4> point);

