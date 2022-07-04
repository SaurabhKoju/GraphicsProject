#pragma once
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