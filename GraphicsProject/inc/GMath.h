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

template <int n>
Vector<n> operator-(Vector<n>, Vector<n>);

float dot(Vector<3> x, Vector<3> y);
Vector<3> normalize(Vector<3> x);


typedef Matrix<3, 3> Mat3;
typedef Matrix<4, 4> Mat4;
typedef Vector<3> Vec3;
typedef Vector<4> Vec4;

#include "GMath.inl"