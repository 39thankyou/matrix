#pragma once
#ifndef MATRIX_STRUC
#define MATRIX_STRUC
#include <iomanip>
#include <iostream>
template <class T>
class vector_matrix;
template <class T>
using default_matrix = vector_matrix<T>;
template <typename T>
class struc_base {
public:
	~struc_base() {}
	virtual const T& cget(int, int) const = 0;
	virtual T& get(int, int) = 0;
	virtual const T& get(int, int) const = 0;
	virtual int row() const = 0;
	virtual int col() const = 0;
	virtual struc_base& operator+=(const struc_base&) = 0;
	virtual struc_base& operator-=(const struc_base&) = 0;
	virtual struc_base& operator*=(const struc_base&) = 0;
	virtual struc_base& operator=(const struc_base&) = 0;
	virtual struc_base& operator=(struc_base&&) = 0;
	virtual void rotation_matrix() = 0;
};
template <typename T>
bool operator==(const struc_base<T>& m1, const struc_base<T>& m2) {
	if (m1.col() != m2.col()) return false;
	if (m1.row() != m2.row()) return false;
	for (int i = 0; i < m1.row(); i++)
		for (int j = 0; j < m1.col; j++)
			if (m1.cget(i, j) != m2.cget(i, j)) return false;
	return true;
}
template <typename T>
decltype(auto) operator*(const struc_base<T>& m1, const struc_base<T>& m2) {
	default_matrix<T> tmp = m1;
	tmp *= m2;
	return tmp;
}
template <typename T>
decltype(auto) operator-(const struc_base<T>& m1, const struc_base<T>& m2) {
	default_matrix<T> tmp = m1;
	tmp -= m2;
	return tmp;
}
template <typename T>
decltype(auto) operator+(const struc_base<T>& m1, const struc_base<T>& m2) {
	default_matrix<T> tmp = m1;
	tmp += m2;
	return tmp;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const struc_base<T>& m) {
	for (int i = 0; i < m.row(); i++) {
		for (int j = 0; j < m.col(); j++) os << std::setw(4) << m.cget(i, j);
		os << '\n';
	}
	return os;
}
template <typename T>
std::istream& operator>>(std::istream& is, struc_base<T>& m) {
	for (int i = 0; i < m.row(); i++)
		for (int j = 0; j < m.col; j++) is >> m.cget(i, j);
	return is;
}
#endif  // !MATRIX
