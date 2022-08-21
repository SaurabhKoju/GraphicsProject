#pragma once

#include <fstream>
#include "Primitives.h"
#include <string>
#include <vector>

std::vector<mesh> LoadObject(std::string mtl_file_path, std::string obj_file_path);
