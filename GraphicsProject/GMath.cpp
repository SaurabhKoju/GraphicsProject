#include "GMath.h"
#include <cmath>

Vector<3> operator*(Vector<3> x, Vector<3> y) {
	Vector<3> p;
	p[0] = x[1] * y[2] - x[2] * y[1];
	p[1] = x[2] * y[0] - x[0] * y[0];
	p[2] = x[0] * y[1] - x[1] * y[0];
	return p;
}

float dot(Vector<3> x, Vector<3> y) {
	return(x[0] * y[0] + x[1] * y[1] + x[2] * y[2]);
}

Vector<3> normalize(Vector<3> x) {
	float m = sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
	return(Vector<3>{ x[0] / m, x[1] / m, x[2] / m });
}