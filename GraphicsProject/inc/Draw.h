#pragma once
#include "GMath.h"
#include <SFML/Graphics.hpp>
#include "Projection.h"
#include "Camera.h"
#include "primitives.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
const float aspect_ratio = float(SCREEN_HEIGHT) / SCREEN_WIDTH;


void drawline(Vector<2> p1, Vector<2> p2, sf::RenderWindow &window);
void draw(mesh M, sf::RenderWindow &window, Camera cam);
