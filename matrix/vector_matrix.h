#pragma once
#include <vector>
#include "matrix_structure.h"

using namespace std;

template<class T>
class vector_matrix :
	public struc_base<T> {
private:
	using data = vector<vector<T>>;
	using base = struc_base<T>;

	data matrix;

public:
	vector_matrix() = default;
	vector_matrix(const data& matrix) :matrix(matrix) {}
	vector_matrix(const vector_matrix& matrix) :matrix(matrix.matrix) {}
	vector_matrix(vector_matrix&& matrix) :matrix(move(matrix.matrix)) {}
	~vector_matrix() = default;

	virtual T& get(int row, int col) override {
		return matrix[row][col];
	}
	virtual const T& get(int row, int col) const override {
		return matrix[row][col];
	}
	virtual int row() const override {
		return matrix.size();
	}
	virtual int col() const override {
		return matrix.size() == 0 ? 0 : matrix[0].size();
	}

	virtual base& operator+=(const base& other) override {
		if (this->matrix.empty()) return *this;
		if (this->col() != other.col() || this->row() != other.row()) {
			return *this; // error
		}
		const auto row_s = row();
		const auto col_s = col();
		for (int i = 0; i < row_s; i++) {
			for (int j = 0; j < col_s; j++) {
				matrix[i][j] += other.get(i, j);
			}
		}
		return *this;
	}

	virtual base& operator-=(const base& other) override {
		if (this->matrix.empty()) return *this;
		if (this->col() != other.col() || this->row() != other.row()) {
			return *this; // error
		}
		const auto row_s = row();
		const auto col_s = col();
		for (int i = 0; i < row_s; i++) {
			for (int j = 0; j < col_s; j++) {
				matrix[i][j] -= other.get(i, j);
			}
		}
		return *this;
	}

	virtual base& operator*=(const base& other) override {
		if (this->matrix.empty()) return *this;
		if (this->col() != other.row()) {
			return *this; // error
		}
		const auto row_s = row();
		const auto col_s = other.col();
		const auto s = this->col();
		data m_temp;
		m_temp.resize(row_s);
		for (auto& i : m_temp) {
			i.resize(col_s);
		}
		swap(m_temp, matrix);
		for (int i = 0; i < row_s; i++) {
			for (int j = 0; j < col_s; j++) {
				for (int k = 0; k < s; k++) {
					matrix[i][j] += get(i, k) * other.get(k, j);
				}
			}
		}
		return *this;
	}

	virtual base& operator=(const base& other) override {
		const auto row_s = other.row();
		const auto col_s = other.col();
		matrix.clear();
		matrix.resize(row_s);
		for (int i = 0; i < row_s; i++) {
			matrix[i].resize(col_s);
		}
		for (int i = 0; i < row_s; i++) {
			for (int j = 0; j < col_s; j++) {
				matrix[i][j] = other.get(i, j);
			}
		}
		return *this;
	}

	virtual base& operator=(base&& other) override {
		auto ptr = dynamic_cast<vector_matrix*>(&other);
		if (ptr != nullptr) {

		}
		return *this;
	}

	virtual void rotation_matrix() override {
	}



};

