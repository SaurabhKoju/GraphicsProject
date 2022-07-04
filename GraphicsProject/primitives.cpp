#include "Primitives.h"

void mesh::transform(Mat4 trasformMatrix) {
	for (triangle& t : triangles) {
		t.p1 = trasformMatrix * t.p1;
		t.p2 = trasformMatrix * t.p2;
		t.p3 = trasformMatrix * t.p3;
		t.p4 = trasformMatrix * t.p4;
	}
}


