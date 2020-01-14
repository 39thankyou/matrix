#include "vector_matrix.h"
#include <tuple>

int main() {
	vector<vector<double>> m;
	m.resize(20);
	for (int i = 0; i < 20; i++) {
		m[i].reserve(20);
		for (int j = 0; j < 20; j++) {
			m[i].emplace_back(i + j);
		}
	}

	vector_matrix<double> matrix{ m };

	cout << matrix << endl;
	cout << (matrix + matrix);
}