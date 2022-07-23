#pragma once
#include <iostream>
#include <math.h>
template <int m, int n>
void Matrix<m, n>::display() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << matrix[i][j] << ' ';
		}
		std::cout << std::endl;
	}
};


template <int m, int n, int o>
Matrix<m, n> operator*(Matrix<m, o> x, Matrix<o, n> y) {
	Matrix<m, n> ans;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			float term = 0;
			for (int k = 0; k < o; k++) {
				term += x.matrix[i][k] * y.matrix[k][j];
			}
			ans.matrix[i][j] = term;
		}
	}
	return ans;
}

template <int n>
Matrix<n, n> inverse(Matrix <n, n> A) {
	/*std::cout << "A:" << std::endl;
	A.display();*/
	Matrix<n, n> ans;
	double a[n][2 * n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2 * n; j++) {
			if (j < n)a[i][j] = A.matrix[i][j];
			else if (j - n == i)a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
	for (int j = 0; j < n; j++) {
		if (fabs(a[j][j]) < 0.00001) {
			std::cout << "Error" << std::endl;
		}
		for (int i = 0; i < n; i++) {
			if (i == j)continue;
			double ratio = a[i][j] / a[j][j];
			for (int k = 0; k < 2 * n; k++) {
				a[i][k] -= ratio * a[j][k];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = n; j < 2 * n; j++) {
			ans.matrix[i][j-n] = a[i][j] / a[i][i];
		}
	}
	/*std::cout << "inverse is " << std::endl;
	ans.display();*/
	return ans;
}

template <int n>
Vector<n> operator*(Matrix<n, n> A, Vector<n> x) {
	Vector<n> ans;
	for (int i = 0; i < n; i++) {
		float term = 0;
		for (int k = 0; k < n; k++) {
			term += A.matrix[i][k] * x[k];
		}
		ans[i] = term;
	}
	return ans;
}

template <int n>
Vector<n> operator-(Vector<n> x, Vector<n> y) {
	Vector<n> ans;
	for (int i = 0; i < n; i++) {
		ans[i] = x[i] - y[i];
	}
	return ans;
}

template <int n>
Vector<n> scale(Vector<n> x, Vector<n> y) {
	Vector<n> ans;
	for (int i = 0; i < n; i++) {
		ans[i] = x[i] * y[i];
	}
	return ans;
}

template <int n>
void Vector<n>::display() {
	for (int i = 0; i < n; i++) {
		std::cout << this->vector[i] << ' ';
	}
	std::cout << std::endl;
}