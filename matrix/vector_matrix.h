#pragma once
#include <vector>
#include <algorithm>
#include "matrix_structure.h"

//using namespace std;

template <class T>
class vector_matrix : public struc_base<T> {
private:
	using data = std::vector<std::vector<T>>;
	using base = struc_base<T>;

	data matrix;

	void resize_row(int row) {
		const auto col = this->col();
		const auto old_row = this->row();
		matrix.resize(row);
		int need_init_row = row > old_row ? row - old_row : 0;
		for (int i = 0; i < need_init_row; i++) {
			matrix[static_cast<size_t>(old_row) + i].resize(col);
		}
	}
	void resize_col(int col) {
		const auto old_row = this->col();
		for (auto& i : matrix) {
			i.resize(col);
		}
	}

    virtual T& get(int row, int col) override { return matrix[row][col]; }
    virtual const T& get(int row, int col) const override {
        return matrix[row][col];
    }
    virtual const T& cget(int row, int col)const override {
        return get(row, col);
    }
    virtual int row() const override { return static_cast<int>(matrix.size()); }
    virtual int col() const override {
        return static_cast<int>(matrix.size() == 0 ? 0 : matrix[0].size());
    }

	virtual T& get(int row, int col) override {
		if (row < 0 || row >= this->row() || col < 0 || col >= this->col())
			throw std::out_of_range("vector_matrix: out of range");
		return matrix[row][col];
	}
	virtual const T& get(int row, int col) const override {
		if (row < 0 || row >= this->row() || col < 0 || col >= this->col())
			throw std::out_of_range("vector_matrix: out of range");
		return matrix[row][col];
	}
	virtual int row() const override { return static_cast<int>(matrix.size()); }
	virtual int col() const override {
		return static_cast<int>(matrix.size() == 0 ? 0 : matrix[0].size());
	}

	virtual base& operator+=(const base& other) override {
		if (this->matrix.empty()) return *this;
		const auto row_s = other.row();
		const auto col_s = other.col();
		resize(std::max(row(), row_s), std::max(col(), col_s));
		for (int i = 0; i < row_s; i++) {
			for (int j = 0; j < col_s; j++) {
				matrix[i][j] += other.get(i, j);
			}
		}
		return *this;
	}
	virtual base& operator-=(const base& other) override {
		if (this->matrix.empty()) return *this;
		const auto row_s = other.row();
		const auto col_s = other.col();
		resize(std::max(row(), row_s), std::max(col(), col_s));
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
			throw std::exception("Parameter error");
		}
		const auto row_s = row();
		const auto col_s = other.col();
		const auto s = this->col();
		vector_matrix m_temp(row_s, col_s);
		swap(m_temp);
		for (int i = 0; i < row_s; i++) {
			for (int j = 0; j < col_s; j++) {
				for (int k = 0; k < s; k++) {
					matrix[i][j] += m_temp.get(i, k) * other.get(k, j);
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
			std::swap(matrix, ptr->matrix);
		} else {
			*this = other;
		}
		return *this;
	}
	virtual base& operator=(const vector_matrix& other) {
		matrix = other.matrix;
		return *this;
	}
	virtual base& operator=(vector_matrix&& other) noexcept {
		matrix = move(other.matrix);
		return *this;
	}

	virtual void rotation_matrix() override {
		if (this->matrix.empty()) return;
		const auto row_s = row();
		const auto col_s = col();
		const auto s = this->col();
		vector_matrix m_temp(col_s, row_s);
		swap(m_temp);
		for (int i = 0; i < col_s; i++) {
			for (int j = 0; j < row_s; j++) {
				matrix[i][j] = m_temp.get(j, i);
			}
		}
	}

	void set_row(int row, std::vector<T> data) {
		const auto col_s = std::min(this->col(), data.size());
		auto& r = matrix[row];
		std::swap_ranges(data.begin(), data.begin() + col_s, r.begin());
	}
	void set_col(int col, std::vector<T> data) {
		const auto col_s = std::min(this->col(), data.size());
		for (int i = 0; i < col_s; i++) {
			std::swap(matrix[i][col], data[i]);
		}
	}
	void resize(int row, int col) {
		resize_row(row);
		resize_col(col);
	}
	void swap(vector_matrix& other) { std::swap(matrix, other.matrix); }
};
