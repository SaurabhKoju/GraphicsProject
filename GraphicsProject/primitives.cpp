#include "Primitives.h"

void mesh::transform(Mat4 trasformMatrix) {
	for (triangle& t : triangles) {
		t.p0 = trasformMatrix * t.p0;
		t.p1 = trasformMatrix * t.p1;
		t.p2 = trasformMatrix * t.p2;		
	}
}


