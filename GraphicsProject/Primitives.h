#pragma once
#include <vector>
#include "GMath.h"
#include <SFML/Graphics.hpp>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
const float aspect_ratio = float(SCREEN_HEIGHT) / SCREEN_WIDTH;

struct material {
	float ka[3], kd[3], ks[3], ns[3];
};

struct triangle {
	Vector<4> p0, p1, p2;
	sf::Color fillColor;
	Vector<4> n0, n1, n2;
};

class mesh {
public:
	std::vector<triangle> triangles;
	void transform(Mat4);
};
