#pragma once
#include <SFML/Graphics.hpp>
#include "Primitives.h"
#include "GMath.h"

sf::Color applyLighting2(Vec4 light, Vec4 normal, Vec4 view, float ambient, material m = { {1, 1, 1}, {0.8, 0.8, 0.8}, {0.5, 0.5, 0.5}, {10, 10, 10} });
