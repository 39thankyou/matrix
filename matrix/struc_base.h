#pragma once
#include "matrix_core.h"

template <typename T>
class const_struc_base {
public:
	using value_type = T;

	virtual ~const_struc_base() {}
	virtual const T& cget(int, int) const = 0;
	virtual const T& get(int, int) const = 0;
	virtual int row() const = 0;
	virtual int col() const = 0;
};

template <typename T>
class struc_base : public const_struc_base<T> {
public:
	using value_type = T;

	virtual ~struc_base() {}
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
bool operator==(const const_struc_base<T>& m1, const const_struc_base<T>& m2) {
	if (m1.col() != m2.col()) return false;
	if (m1.row() != m2.row()) return false;
	for (int i = 0; i < m1.row(); i++)
		for (int j = 0; j < m1.col; j++)
			if (m1.cget(i, j) != m2.cget(i, j)) return false;
	return true;
}

template <typename T>
decltype(auto) operator*(const const_struc_base<T>& m1,
	const const_struc_base<T>& m2) {
	return op::bin_expr<const_struc_base<T>, const_struc_base<T>, op::mult>{
		m1, m2, op::mult{}};
}
template <typename T>
decltype(auto) operator-(const const_struc_base<T>& m1,
	const const_struc_base<T>& m2) {
	return op::bin_expr<const_struc_base<T>, const_struc_base<T>, op::minus>{
		m1, m2, op::minus{}};
}
template <typename T>
decltype(auto) operator+(const const_struc_base<T>& m1,
	const const_struc_base<T>& m2) {
	return op::bin_expr<const_struc_base<T>, const_struc_base<T>, op::plus>{
		m1, m2, op::plus{}};
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const const_struc_base<T>& m) {
	for (int i = 0; i < m.row(); i++) {
		for (int j = 0; j < m.col(); j++) {
			os << std::setw(4) << m.cget(i, j);
		}
		os << '\n';
	}
	return os;
}
template <typename T>
std::istream& operator>>(std::istream& is, struc_base<T>& m) {
	for (int i = 0; i < m.row(); i++) {
		for (int j = 0; j < m.col; j++) {
			is >> m.cget(i, j);
		}
	}
	return is;
}

template <class T>
inline decltype(auto) __get_default_value__(std::true_type) {
	return T{};
}
template <class T>
inline decltype(auto) __get_default_value__(std::false_type) {
	return static_cast<T>(0);
}

template <class T>
decltype(auto) get_default_value() {
	return __get_default_value__<T>(std::bool_constant<std::is_class_v<T>>{});
}
