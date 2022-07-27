#include "ObjectLoader.h"
#include <map>
#include <sstream>
#include "GMath.h"

mesh LoadObject(std::string mtl_file_path, std::string obj_file_path) {
	mesh object;


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
			for (int i = 0; i < 9; i++) {
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
	material current_material;
	while (std::getline(obj_file, line)) {
		std::istringstream iss(line);
		std::string first_token;
		iss >> first_token;
		if (first_token == "v") {
			float x, y, z;
			iss >> x >> y >> z;
			vertices.push_back(Vec4{ x, y, z, 1 });
		}
		else if (first_token == "usemtl") {
			std::string material_name;
			iss >> material_name;
			current_material = mtlmap[material_name];
		}
		else if(first_token == "f") {
			std::string v1, v2, v3;
			iss >> v1 >> v2 >> v3;
			v1 = v1.substr(0, v1.find("/"));
			v2 = v2.substr(0, v2.find("/"));
			v3 = v3.substr(0, v3.find("/"));

			triangle t{vertices[stoi(v1)-1], vertices[stoi(v2)-1], vertices[stoi(v3)-1]};
			t.mtl = current_material;
			object.triangles.push_back(t);
		}
	}

	return object;
}