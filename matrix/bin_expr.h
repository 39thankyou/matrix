#pragma once
#include "matrix_core.h"
#include "vector_matrix.h"

namespace op {

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

	struct plus {
		using is_transparent = int;

		template <class _Ty1, class _Ty2>
		constexpr auto operator()(_Ty1&& _Left, _Ty2&& _Right) const
			noexcept(noexcept(static_cast<_Ty1&&>(_Left) +
				static_cast<_Ty2&&>(_Right)))  // strengthened
			-> decltype(static_cast<_Ty1&&>(_Left) + static_cast<_Ty2&&>(_Right)) {
			return static_cast<_Ty1&&>(_Left) + static_cast<_Ty2&&>(_Right);
		}
	};
	struct minus {
		using is_transparent = int;

		template <class _Ty1, class _Ty2>
		constexpr auto operator()(_Ty1&& _Left, _Ty2&& _Right) const
			noexcept(noexcept(static_cast<_Ty1&&>(_Left) -
				static_cast<_Ty2&&>(_Right)))  // strengthened
			-> decltype(static_cast<_Ty1&&>(_Left) - static_cast<_Ty2&&>(_Right)) {
			return static_cast<_Ty1&&>(_Left) - static_cast<_Ty2&&>(_Right);
		}
	};
	struct mult {
		using is_transparent = int;

		template <class _Ty1, class _Ty2>
		constexpr auto operator()(_Ty1&& _Left, _Ty2&& _Right) const
			noexcept(noexcept(static_cast<_Ty1&&>(_Left)*
				static_cast<_Ty2&&>(_Right)))  // strengthened
			-> decltype(static_cast<_Ty1&&>(_Left)* static_cast<_Ty2&&>(_Right)) {
			return static_cast<_Ty1&&>(_Left)* static_cast<_Ty2&&>(_Right);
		}
	};

	template <class T, class OP>
	inline decltype(auto) __eval__(const const_struc_base<T>& a,
		const const_struc_base<T>& b, OP op,
		std::true_type, std::true_type) {
		return default_matrix<T>{op(static_cast<const struc_base<T>&>(a),
			static_cast<const struc_base<T>&>(b))};
	}
	template <class T, class OP>
	inline decltype(auto) __eval__(const const_struc_base<T>& a,
		const const_struc_base<T>& b, OP op,
		std::false_type, std::true_type) {
		return default_matrix<T>{op(static_cast<const default_matrix<T>&>(a),
			static_cast<const struc_base<T>&>(b))};
	}
	template <class T, class OP>
	inline decltype(auto) __eval__(const const_struc_base<T>& a,
		const const_struc_base<T>& b, OP op,
		std::true_type, std::false_type) {
		return default_matrix<T>{op(static_cast<const struc_base<T>&>(a),
			static_cast<const default_matrix<T>&>(b))};
	}
	template <class T, class OP>
	inline decltype(auto) __eval__(const const_struc_base<T>& a,
		const const_struc_base<T>& b, OP op,
		std::false_type, std::false_type) {
		return default_matrix<T>{op(static_cast<const default_matrix<T>&>(a),
			static_cast<const default_matrix<T>&>(b))};
	}

	template <class T, class U, class OP>
	class bin_expr : public const_struc_base<typename T::value_type> {
	public:
		using value_type = typename T::value_type;
		using base = const_struc_base<value_type>;
		using _base = struc_base<value_type>;

		explicit bin_expr(const T& m, const U& e, OP op = OP{})
			: _m(m), _e(e), _op(op), temp_result(new value_type) {
		}
		~bin_expr() {
			if (temp_result != nullptr) delete temp_result;
		}
		inline decltype(auto) operator()() const {
			return __eval__(_m, _e, _op,
				std::bool_constant<std::is_base_of_v<_base, T>>{},
				std::bool_constant<std::is_base_of_v<_base, U>>{});
		}
		inline operator default_matrix<value_type>() const {
			return __eval__(_m, _e, _op,
				std::bool_constant<std::is_base_of_v<_base, T>>{},
				std::bool_constant<std::is_base_of_v<_base, U>>{});
		}

		virtual const value_type& cget(int row, int col) const override {
			return get(row, col);
		}
		virtual const value_type& get(int row, int col) const override {
			if (row < 0 || row >= this->row() || col < 0 || col >= this->col()) {
				*temp_result = get_default_value<value_type>();
				return *temp_result;
			}
			value_type a = get_default_value<value_type>(),
				b = get_default_value<value_type>();
			try {
				a = _m.get(row, col);
			} catch (const std::exception&) {
			}
			try {
				b = _e.get(row, col);
			} catch (const std::exception&) {
			}
			*temp_result = _op(a, b);
			return *temp_result;
		}
		virtual int row() const override { return std::max(_m.row(), _e.row()); }
		virtual int col() const override { return std::max(_m.col(), _e.col()); }

	private:
		const T& _m;
		const U& _e;
		OP _op;
		value_type* temp_result;
	};

	template <class T, class U>
	class bin_expr<T, U, mult> : public const_struc_base<typename T::value_type> {
	public:
		using value_type = typename T::value_type;
		using base = const_struc_base<value_type>;
		using _base = struc_base<value_type>;

		explicit bin_expr(const T& m, const U& e, mult op = mult{})
			: _m(m), _e(e), _op(op), temp_result(new value_type) {
		}
		~bin_expr() {
			if (temp_result != nullptr) delete temp_result;
		}
		inline decltype(auto) operator()() const {
			return __eval__(_m, _e, _op,
				std::bool_constant<std::is_base_of_v<_base, T>>{},
				std::bool_constant<std::is_base_of_v<_base, U>>{});
		}
		inline operator default_matrix<value_type>() const {
			return __eval__(_m, _e, _op,
				std::bool_constant<std::is_base_of_v<_base, T>>{},
				std::bool_constant<std::is_base_of_v<_base, U>>{});
		}

		virtual const value_type& cget(int row, int col) const override {
			return get(row, col);
		}
		virtual const value_type& get(int row, int col) const override {
			if (row < 0 || row >= this->row() || col < 0 || col >= this->col()) {
				*temp_result = get_default_value<value_type>();
				return *temp_result;
			}
			if (_m.col() != _e.row()) {
				throw std::exception("Parameter error");
			}
			const auto s = _m.col();
			*temp_result = _m.get(row, 0) * _e.get(0, col);
			for (int k = 1; k < s; k++) {
				*temp_result += _m.get(row, k) * _e.get(k, col);
			}
			return *temp_result;
		}
		virtual int row() const override { return _m.row(); }
		virtual int col() const override { return _e.col(); }

	private:
		const T& _m;
		const U& _e;
		mult _op;
		value_type* temp_result;
	};

}  // namespace op