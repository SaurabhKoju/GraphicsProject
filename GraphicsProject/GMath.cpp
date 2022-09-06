#include "GMath.h"
#include <cmath>

float min(float x, float y) { return x < y ? x : y; }
float max(float x, float y) { return x > y ? x : y; }

Vec4 operator/(Vec4 x, float a) {
	Vector<4> p;
	p[0] = x[0] / a;
	p[1] = x[1] / a;
	p[2] = x[2] / a;
	p[3] = x[3] / a;
	return p;
}

Vec4 operator*(Vector<4> x, Vector<4> y) {
	Vec4 p;
	p[0] = x[1] * y[2] - x[2] * y[1];
	p[1] = x[2] * y[0] - x[0] * y[2];
	p[2] = x[0] * y[1] - x[1] * y[0];
	p[3] = 1;
	return p;
}

float magnitudeSquared(Vec4 x) {
	return x[0] * x[0] + x[1] * x[1] + x[2] * x[2];
}

float magnitude(Vec4 x) {
	return sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
}

float dot(Vec4 x, Vec4 y) {
	return(x[0] * y[0] + x[1] * y[1] + x[2] * y[2]);
}

Vec4 normalize(Vec4 x) {
	float m = sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
	return(Vec4{ x[0] / m, x[1] / m, x[2] / m , 1});
}

Mat4 getScaleMatrix(Vec4 s) {
	return(Mat4{
		s[0], 0, 0, 0,
		0, s[1], 0, 0,
		0, 0, s[2], 0,
		0, 0, 0, 1
		});
}

Mat4 getTranslateMatrix(Vec4 t) {
	return(Mat4{
		1, 0, 0, t[0],
		0, 1, 0, t[1],
		0, 0, 1, t[2],
		0, 0, 0, 1
		});
}

Mat4 getTransformMatrix(Vec4 a, Vec4 b, Vec4 c) {
	return(Mat4{
		a[0], b[0], c[0], 0,
		a[1], b[1], c[1], 0,
		a[2], b[2], c[2], 0,
		0, 0, 0, 1
		});
}

Mat4 transpose(Mat4 x) {
	Mat4 ans;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ans.matrix[i][j] = x.matrix[j][i];
		}
	}
	return ans;
}

Mat4 rotateAboutZ(float angle) {
	angle *= pi/180;
	return(Mat4{
		cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		});
}


Mat4 rotateAboutY(float angle) {
	angle *= pi / 180;
	return(Mat4{
		cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1
		});
}

Mat4 rotateAboutX(float angle) {
	angle *= pi / 180;
	return(Mat4{
		1, 0, 0, 0,
		0, cos(angle), -sin(angle), 0,
		0, sin(angle), cos(angle), 0,
		0, 0, 0, 1
		});
}

Mat4 getRotationMatrix(Vec4 p, Vec4 v, float angle) {
	if (v[1] == 0 && v[2] == 0) {
		if (v[0] < 0) {
			return getTranslateMatrix(p) * rotateAboutX(-angle) * getTranslateMatrix(Vec4{ 0, 0, 0, 0 } - p);
		}
		return getTranslateMatrix(p) * rotateAboutX(angle)* getTranslateMatrix(Vec4{ 0, 0, 0, 0 } - p);
	}

	Vec4 uz = normalize(v);
	Vec4 uy = normalize(Vec4{ 1, 0, 0, 0 } * uz);
	Vec4 ux = uy * uz;

	Mat4 rotate2 = getTransformMatrix(ux, uy, uz);
	Mat4 rotate1 = transpose(rotate2);

	return getTranslateMatrix(p) * rotate2 * rotateAboutZ(angle) * rotate1 * getTranslateMatrix(Zero4-p);
}
