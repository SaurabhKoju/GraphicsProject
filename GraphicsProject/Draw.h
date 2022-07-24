#pragma once
#include "GMath.h"
#include <SFML/Graphics.hpp>
#include "Projection.h"
#include "Camera.h"
#include "Primitives.h"


void draw(mesh M, sf::RenderWindow &window, Camera cam, Vec4 light);
