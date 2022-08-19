#pragma once
#include <SFML/Graphics.hpp>
#include "Primitives.h"
#include "GMath.h"

sf::Color applyLighting(Vec4 light, Vec4 normal, Vec4 view, float ambient, material m = default_material);
