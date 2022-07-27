#pragma once

#include <fstream>
#include "primitives.h"
#include <string>

mesh LoadObject(std::string mtl_file_path, std::string obj_file_path);
