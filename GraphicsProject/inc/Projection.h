#pragma once
#include "GMath.h"
#include <vector>

struct triangle {
	Vector<3> p1, p2, p3;
};

struct mesh {
	std::vector<triangle> triangles;
};

Vector<2> get2d(Vector<3> point);

