#pragma once
#include <iostream>
#include <cmath>
const double pi = 3.141592654;

float min(float x, float y);
float max(float x, float y);


template <int m, int n>
class Matrix {
public:
	float matrix[m][n];
	void display();
};
template <int m, int n, int o>
Matrix<m, n> operator*(Matrix<m, o> x, Matrix<o, n> y);

template <int n>
Matrix<n, n> inverse(Matrix <n, n>);


template <int n>
class Vector {
public:
	float vector[n];
	void display();
	float& operator[](int i) {
		return vector[i];
	
	}
};

typedef Matrix<3, 3> Mat3;
typedef Matrix<4, 4> Mat4;
typedef Vector<3> Vec3;
typedef Vector<4> Vec4;
const Vec4 Zero4 = { 0, 0, 0, 0 };



template <int n>
Vector<n> operator*(Matrix<n, n>, Vector<n>);

Vec4 operator*(Vec4, Vec4);
Vec4 operator/(Vec4, float a);


template <int n>
Vector<n> operator-(Vector<n>, Vector<n>);
template <int n>
Vector<n> operator+(Vector<n>, Vector<n>);
template <int n>
Vector<n> operator*(float scalar, Vector<n>);
template <int n>
bool operator==(Vector<n>, Vector<n>);

float dot(Vec4 x, Vec4 y);
Vec4 normalize(Vec4 x);
float magnitudeSquared(Vec4);


Mat4 getScaleMatrix(Vec4 s);
Mat4 getTranslateMatrix(Vec4 t);
Mat3 getTransformMatrix(Vec4 a, Vec4 b, Vec4 c);
Mat4 getRotationMatrix(Vec4 tail, Vec4 head, float angle); //angle in degrees
Mat4 rotateAboutZ(float angle);
Mat4 rotateAboutY(float angle);
Mat4 rotateAboutX(float angle);

#include "GMath.inl"
