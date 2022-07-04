#pragma once
#include <vector>
#include "GMath.h"

struct triangle {
	Vector<4> p1, p2, p3, p4;
};

class mesh {
public:
	std::vector<triangle> triangles;
	void transform(Mat4);
};
