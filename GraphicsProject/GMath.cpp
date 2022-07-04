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

Mat4 getScaleMatrix(Vector<3> s) {
	return(Mat4{
		s[0], 0, 0, 0,
		0, s[1], 0, 0,
		0, 0, s[2], 0,
		0, 0, 0, 1
		});
}

Mat4 getTranslateMatrix(Vector<3> t) {
	return(Mat4{
		1, 0, 0, t[0],
		0, 1, 0, t[1],
		0, 0, 1, t[2],
		0, 0, 0, 1
		});
}

Mat4 getTransformMatrix(Vector<3> a, Vector<3> b, Vector<3> c) {
	return(Mat4{
		a[0], b[0], c[0], 0,
		a[1], b[1], c[1], 0,
		a[2], b[2], c[2], 1
		});
}