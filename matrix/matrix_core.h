#pragma once

#include <algorithm>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <vector>

template <typename T>
class const_struc_base;
template <typename T>
class struc_base;
template <typename T>
class adjacent_list_matrix;
template <class T>
class vector_matrix;
template <class T>
using default_matrix = vector_matrix<T>;

template <typename T>
bool operator==(const const_struc_base<T>&, const const_struc_base<T>&);

template <typename T>
decltype(auto) operator*(const const_struc_base<T>&,
	const const_struc_base<T>&);
template <typename T>
decltype(auto) operator-(const const_struc_base<T>&,
	const const_struc_base<T>&);
template <typename T>
decltype(auto) operator+(const const_struc_base<T>&,
	const const_struc_base<T>&);

template <typename T>
std::ostream& operator<<(std::ostream& os, const const_struc_base<T>& m);
template <typename T>
std::istream& operator>>(std::istream& is, struc_base<T>& m);

template <class T>
decltype(auto) get_default_value();

namespace op {
	struct plus;
	struct minus;
	struct mult;

	template <class T, class U, class OP>
	class bin_expr;
}  // namespace op

#include "bin_expr.h"
#include "struc_base.h"
