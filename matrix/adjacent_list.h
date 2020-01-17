#pragma once
#include "matrix_core.h"

template <typename T>
class adjacent_list_matrix : public struc_base<T> {
protected:
	using node_type = std::pair<int, T>;
	using row_type = std::list<node_type>;
	using matrix_struc_type = std::vector<row_type>;
	std::shared_ptr<matrix_struc_type> pmtx;
	bool is_rotation{ false };
	int col_size;
	T default_value;
	decltype(auto) _get(int, int) const;
	struc_base<T>& operator_diy(const struc_base<T>&,
		std::function<void(T&, const T&)>);

public:
	using value_type = T;

	adjacent_list_matrix(int row, int col,
		const T& default_value = get_default_value<T>())
		: pmtx(std::make_shared<matrix_struc_type>(row, row_type())),
		col_size(col),
		default_value(default_value) {
	}
	adjacent_list_matrix(const adjacent_list_matrix& a)
		: pmtx(std::make_shared<matrix_struc_type>(*a.pmtx)),
		col_size(a.col()),
		default_value(a.default_value) {
	}
	adjacent_list_matrix(adjacent_list_matrix&& a) = default;

	virtual const T& cget(int r, int c) const override {
		if (is_rotation) std::swap(r, c);
		auto iter = _get(r, c);
		if (iter == (*pmtx)[r].end())
			return default_value;
		else
			return iter->second;
	}
	virtual const T& get(int r, int c) const override { return cget(r, c); }
	virtual T& get(int r, int c) override {
		if (is_rotation) std::swap(r, c);
		auto iter = _get(r, c);
		if (iter == (*pmtx)[r].end()) {
			(*pmtx)[r].push_back({ c, default_value });
			return (*pmtx)[r].back().second;
		} else
			return iter->second;
	}
	virtual int row() const override {
		return static_cast<int>(!is_rotation ? pmtx->size() : col_size);
	}
	virtual int col() const override {
		return static_cast<int>(is_rotation ? pmtx->size() : col_size);
	}

	virtual struc_base<T>& operator+=(const struc_base<T>& m) override {
		operator_diy(m, [](T& target, const T& val) { target += val; });
		return *this;
	}
	virtual struc_base<T>& operator-=(const struc_base<T>& m) override {
		operator_diy(m, [](T& target, const T& val) { target -= val; });
		return *this;
	}
	virtual struc_base<T>& operator*=(const struc_base<T>& m) override {
		if (col() != m.row()) throw std::exception("illegal input");
		adjacent_list_matrix<T> tmp{ row(), m.col(), default_value };

		for (int i = 0; i < this->row(); i++)
			for (int j = 0; j < m.col(); j++) {
				T val = default_value;
				for (int k = 0; k < col(); k++) {
					T val1 = cget(i, k);
					T val2 = m.cget(k, j);
					if (val1 != default_value && val2 != default_value)
						val += val1 * val2;
				}
				if (val != default_value) tmp.get(i, j) = val;
			}
		*this = static_cast<struc_base<T>&>(tmp);
		return *this;
	}
	virtual struc_base<T>& operator=(const struc_base<T>& m) override {
		this->pmtx = std::make_shared<matrix_struc_type>(m.row(), row_type());
		this->col_size = m.col();
		for (int i = 0; i < this->row(); i++)
			for (int j = 0; j < this->col(); j++) {
				T val = m.cget(i, j);
				if (m.cget(i, j) == default_value)
					continue;
				else
					this->get(i, j) = val;
			}
		return *this;
	}
	virtual struc_base<T>& operator=(struc_base<T>&& m) override {
		*this = m;
		return *this;
	}

	virtual void rotation_matrix() override { is_rotation = !is_rotation; }
};

template <typename T>
struc_base<T>& adjacent_list_matrix<T>::operator_diy(
	const struc_base<T>& m, std::function<void(T&, const T&)> f) {
	if (this->col() != m.col()) throw std::exception("col is not same");
	if (this->row() != m.row()) throw std::exception("row is not same");
	for (int i = 0; i < this->row(); i++)
		for (int j = 0; j < this->col(); j++) {
			T val = m.cget(i, j);
			if (val == default_value)
				continue;
			else
				f(get(i, j), val);
		}
	return *this;
}

template <typename T>
decltype(auto) adjacent_list_matrix<T>::_get(int row, int col) const {
	int col_num = this->col_size;
	if (is_rotation) col_num = this->row();
	if (col < 0 || col > col_num) throw std::out_of_range("pos out of range");
	auto iter =
		std::find_if((*pmtx)[row].begin(), (*pmtx)[row].end(),
			[=](const node_type& node) { return node.first == col; });

	return iter;
}
