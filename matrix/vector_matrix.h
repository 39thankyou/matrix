#pragma once
#include <vector>
#include "matrix_structure.h"

using namespace std;

template <class T>
class vector_matrix : public struc_base<T> {
   private:
    using data = vector<vector<T>>;
    using base = struc_base<T>;

    data matrix;

   public:
    vector_matrix() = default;
    vector_matrix(int row, int col) : matrix(row) {
        for (auto& i : matrix) {
            i.resize(col);
        }
    }
    vector_matrix(const data& matrix) : matrix(matrix) {}
    vector_matrix(const vector_matrix& matrix) : matrix(matrix.matrix) {}
    vector_matrix(vector_matrix&& matrix) noexcept
        : matrix(move(matrix.matrix)) {}
    vector_matrix(const base& other) {
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
    }
    vector_matrix(base&& other) {
        auto ptr = dynamic_cast<vector_matrix*>(&other);
        if (ptr != nullptr) {
            swap(matrix, ptr->matrix);
        } else {
            *this = other;
        }
    }
    ~vector_matrix() = default;

    virtual T& get(int row, int col) override { return matrix[row][col]; }
    virtual const T& get(int row, int col) const override {
        return matrix[row][col];
    }
    virtual int row() const override { return static_cast<int>(matrix.size()); }
    virtual int col() const override {
        return static_cast<int>(matrix.size() == 0 ? 0 : matrix[0].size());
    }

    virtual base& operator+=(const base& other) override {
        if (this->matrix.empty()) return *this;
        if (this->col() != other.col() || this->row() != other.row()) {
            return *this;  // error
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
            return *this;  // error
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
            return *this;  // error
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

    void set_row(int row, vector<T> data) {
        const auto col_s = col();
        const auto col_s_ = data.size();
        auto& r = matrix[row];
        copy(data.begin(), data.begin() + min(col_s, col_s_), r.begin());
    }

    void swap(vector_matrix& other) { std::swap(matrix, other.matrix); }
};
