#pragma once
#include <vector>
#include "GMath.h"
#include <SFML/Graphics.hpp>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
const float aspect_ratio = float(SCREEN_HEIGHT) / SCREEN_WIDTH;

struct triangle {
<<<<<<< Updated upstream
	Vector<4> p0, p1, p2;
=======
	Vec4 p1, p2, p3, p4;
>>>>>>> Stashed changes
	sf::Color fillColor;
};

class mesh {
public:
	std::vector<triangle> triangles;
	void transform(Mat4);
};
