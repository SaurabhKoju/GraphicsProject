#pragma once
#include "GMath.h"
#include <SFML/Graphics.hpp>
#include "Projection.h"
#include "Camera.h"
#include "Primitives.h"


void drawline(Vector<2> p1, Vector<2> p2, sf::RenderWindow &window);
void draw(mesh M, sf::RenderWindow &window, Camera cam, Vec3 light);
