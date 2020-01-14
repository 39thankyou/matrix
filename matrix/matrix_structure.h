#pragma once
#ifndef MATRIX_STRUC
#define MATRIX_STRUC
#include<iostream>
template<typename T>
class struc_base
{
public:
	~struc_base() {}
	virtual T& get(int, int)const = 0;
	virtual int row()const = 0;
	virtual int col()const = 0;
	virtual struc_base& operator+=(const struc_base&) = 0;
	virtual struc_base& operator-=(const struc_base&) = 0;
	virtual struc_base& operator*=(const struc_base&) = 0;
	virtual struc_base& operator=(const struc_base&) = 0;
	virtual struc_base& operator=(struc_base&&) = 0;
	virtual void rotation_matrix() = 0;
};
template<typename T>
bool operator==(const struc_base<T>& m1, const struc_base<T>& m2)
{
	if (m1.col() != m2.col())return false;
	if (m1.row() != m2.row())return false;
	for (int i = 0; i < m1.row(); i++)
		for (int j = 0; j < m1.col; j++)
			if (m1.get(i, j) != m2.get(i, j))return false;
	return true;
}
template<typename T>
struc_base<T> operator*(const struc_base<T>& m1, const struc_base<T>& m2)
{
	auto tmp = m1;
	tmp *= m2;
	return tmp;
}
template<typename T>
struc_base<T> operator-(const struc_base<T>& m1, const struc_base<T>& m2)
{
	auto tmp = m1;
	tmp -= m2;
	return tmp;
}
template<typename T>
struc_base<T> operator+(const struc_base<T>& m1, const struc_base<T>& m2)
{
	auto tmp = m1;
	tmp += m2;
	return tmp;
}
template<typename T>
std::ostream& operator<<(const struc_base<T>& m, std::ostream& os)
{
	for (int i = 0; i < m.row(); i++)
		for (int j = 0; j < m.col; j++)
			os << m.get(i, j);
}
template<typename T>
std::istream& operator>>(struc_base<T>& m, std::istream& is)
{
	for (int i = 0; i < m.row(); i++)
		for (int j = 0; j < m.col; j++)
			is >> m.get(i, j);
}
#endif // !MATRIX
