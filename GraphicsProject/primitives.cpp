#include "Primitives.h"

void mesh::transform(Mat4 trasformMatrix) {
	for (triangle& t : triangles) {
		t.p0 = trasformMatrix * t.p0;
		t.p1 = trasformMatrix * t.p1;
		t.p2 = trasformMatrix * t.p2;	

		t.n0 = trasformMatrix * t.n0;
		t.n1 = trasformMatrix * t.n1;
		t.n2 = trasformMatrix * t.n2;
	}
}


