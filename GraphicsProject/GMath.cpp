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

Mat3 getTransformMatrix(Vec4 a, Vec4 b, Vec4 c) {
	return(Mat3{
		a[0], b[0], c[0],
		a[1], b[1], c[1],
		a[2], b[2], c[2]
		});
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

Mat4 rotateAboutZ(float cosine, float sine) {
	return(Mat4{
		cosine, -sine, 0, 0,
		sine, cosine, 0, 0,
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

Mat4 rotateAboutY(float cosine, float sine) {
	return(Mat4{
		cosine, 0, sine, 0,
		0, 1, 0, 0,
		-sine, 0, cosine, 0,
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

Mat4 rotateAboutX(float cosine, float sine) {
	return(Mat4{
		1, 0, 0, 0,
		0, cosine, -sine, 0,
		0, sine, cosine, 0,
		0, 0, 0, 1
		});
}

Mat4 getRotationMatrix(Vec4 tail, Vec4 head, float angle) {
	Vec4 v = head - tail;
	if (v[1] == 0 && v[2] == 0) {
		if (v[0] < 0) {
			return getTranslateMatrix(tail) * rotateAboutX(-angle) * getTranslateMatrix(Vec4{ 0, 0, 0, 0 } - tail);
		}
		return getTranslateMatrix(tail) * rotateAboutX(angle)* getTranslateMatrix(Vec4{ 0, 0, 0, 0 } - tail);
	}
	float Xanglecosine = v[1] / sqrt(v[1]*v[1] + v[2]*v[2]);
	float Xanglesine = v[2] / sqrt(v[1]*v[1] + v[2]*v[2]);
	Mat4 Xrotate = rotateAboutX(Xanglecosine, -Xanglesine);
	Mat4 Xantirotate = rotateAboutX(Xanglecosine, Xanglesine);
	float Zanglecosine = v[0] / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	float Zanglesine = sqrt(v[1]*v[1] + v[2]*v[2]) / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	Mat4 Zrotate = rotateAboutZ(Zanglecosine, -Zanglesine);
	Mat4 Zantirotate = rotateAboutZ(Zanglecosine, Zanglesine);

	return getTranslateMatrix(tail) * Xantirotate * Zantirotate * rotateAboutX(angle) * Zrotate * Xrotate * getTranslateMatrix(Vec4{0, 0, 0, 0}-tail);
}
