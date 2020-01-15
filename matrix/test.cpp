#include "vector_matrix.h"
#include <tuple>

int main() {
	constexpr int size = 3;
	vector<vector<double>> m;
	m.resize(size);
	for (int i = 0; i < size; i++) {
		m[i].reserve(size);
		for (int j = 0; j < size; j++) {
			m[i].emplace_back(i + 2 * j);
		}
	}

	vector_matrix<double> matrix{ m };
	struc_base<double>& base = matrix;

	cout << "matrix:\n";
	cout << base << endl;
	cout << "matrix * matrix:\n";
	cout << (base * base) << endl;
	cout << "rotation:\n";
	base.rotation_matrix();
	cout << base << endl;
}