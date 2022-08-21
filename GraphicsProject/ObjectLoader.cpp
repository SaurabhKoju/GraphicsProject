#include "ObjectLoader.h"
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include "GMath.h"

std::vector<mesh> LoadObject(std::string mtl_file_path, std::string obj_file_path) {
	std::vector<mesh> object;
	mesh small_cube;


	std::ifstream mtl_file(mtl_file_path);
	std::ifstream obj_file(obj_file_path);

	std::map<std::string, material> mtlmap;

	std::string line;
	while (std::getline(mtl_file, line)) {
		std::istringstream iss(line);
		std::string first_token;
		iss >> first_token;
		if (first_token == "#")continue;
		if (first_token == "newmtl") {
			std::string material_name;
			iss >> material_name;
			material m;
			m.name = material_name;
			while(true) {
				getline(mtl_file, line);
				std::istringstream pss(line);
				pss.str(line);
				std::string properties;
				pss >> properties;
				if (properties == "Ns") {
					pss >> m.ns;
				}
				else if (properties == "Ka") {
					pss >> m.ka[0] >> m.ka[1] >> m.ka[2];
				}
				else if (properties == "Ks") {
					pss >> m.ks[0] >> m.ks[1] >> m.ks[2];
				}
				else if (properties == "Kd") {
					pss >> m.kd[0] >> m.kd[1] >> m.kd[2];
				}
				else if (properties == "illum" || properties == "Ke" || properties == "Ni" || properties == "d");
				else break;
			}
			mtlmap[material_name] = m;
		}
	}


	std::vector<Vec4> vertices;
	std::vector<Vec4> normals;
	material current_material = default_material;
	while (std::getline(obj_file, line)) {
		std::istringstream iss(line);
		std::string first_token;
		iss >> first_token;
		if (first_token == "v") {
			float x, y, z;
			iss >> x >> y >> z;
			vertices.push_back(Vec4{ x, y, z, 1 });
		}
		else if (first_token == "vn") {
			float x, y, z;
			iss >> x >> y >> z;
			normals.push_back(Vec4{ x, y, z, 1 });
		}
		else if (first_token == "usemtl") {
			std::string material_name;
			iss >> material_name;
			current_material = mtlmap[material_name];
		}
		else if (first_token == "o") {
			if (!small_cube.triangles.size())continue;
			object.push_back(small_cube);
			small_cube = mesh();
		}
		else if(first_token == "f") {
			std::string v1, v2, v3;
			iss >> v1 >> v2 >> v3;
			std::string x1 = v1.substr(0, v1.find("/"));
			std::string x2 = v2.substr(0, v2.find("/"));
			std::string x3 = v3.substr(0, v3.find("/"));
			triangle t{vertices[stoi(x1)-1], vertices[stoi(x2)-1], vertices[stoi(x3)-1]};

			if (std::count(v1.begin(), v1.end(), '/') == 2) {
				int first_pos = v1.find("/");
				int second_pos = v1.find("/", first_pos + 1);

				std::string n0 = v1.substr(second_pos + 1, v1.size() - second_pos - 1);

				first_pos = v2.find("/");
				second_pos = v2.find("/", first_pos + 1);
				std::string n1 = v2.substr(second_pos + 1, v2.size() - second_pos - 1);

				first_pos = v3.find("/");
				second_pos = v3.find("/", first_pos + 1);
				std::string n2 = v3.substr(second_pos + 1, v3.size() - second_pos - 1);
				t.n0 = normals[stoi(n0) - 1];
				t.n1 = normals[stoi(n1) - 1];
				t.n2 = normals[stoi(n2) - 1];
				t.normals_present = true;
			}
			t.mtl = current_material;
			small_cube.triangles.push_back(t);
		}
	}

	if (small_cube.triangles.size() != 0) {
		object.push_back(small_cube);
		small_cube = mesh();
	}

	return object;
}