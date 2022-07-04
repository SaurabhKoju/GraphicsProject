#pragma once
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
const float aspect_ratio = float(SCREEN_HEIGHT) / SCREEN_WIDTH;
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
