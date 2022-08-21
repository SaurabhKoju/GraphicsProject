#pragma once
#include "GMath.h"
#include <SFML/Graphics.hpp>
#include "Projection.h"
#include "Camera.h"
#include "Primitives.h"


void draw(mesh M, sf::RenderWindow& window, Camera cam, Vec4 light, std::vector < std::vector<float> > &zbuffer, std::vector<std::vector<Vec4> > &nbuffer);
