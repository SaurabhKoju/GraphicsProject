#pragma once
#include <iostream>

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
template <int n>
Vector<n> operator*(Matrix<n, n>, Vector<n>);

Vector<3> operator*(Vector<3>, Vector<3>);
Vector<3> operator+(Vector<3>, Vector<3>);
Vector<4> operator+(Vector<4>, Vector<4>);
Vector<4> operator/(Vector<4>, float a);
Vector<3> operator*(Vector<4>, Vector<4>);

template <int n>
Vector<n> operator-(Vector<n>, Vector<n>);

float dot(Vector<3> x, Vector<3> y);
Vector<3> normalize(Vector<3> x);





typedef Matrix<3, 3> Mat3;
typedef Matrix<4, 4> Mat4;
typedef Vector<3> Vec3;
typedef Vector<4> Vec4;


Mat4 getScaleMatrix(Vector<3> s);
Mat4 getTranslateMatrix(Vector<3> t);
Mat3 getTransformMatrix(Vector<3> a, Vector<3> b, Vector<3> c);
Mat4 getRotationMatrix(Vector<3> tail, Vector<3> head, float angle); //angle in degrees
Mat4 rotateAboutZ(float angle);
Mat4 rotateAboutY(float angle);
Mat4 rotateAboutX(float angle);

#include "GMath.inl"
