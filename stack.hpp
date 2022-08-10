#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <typename T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T			value_type;
		typedef Container	container_type;
	
	protected:
		container_type		m_con;
	
	public:
		explicit stack(const container_type &container = container_type()) : m_con(container) {}
		stack(const stack &origin) : m_con(origin.m_con) {}
		~stack() {}

		stack &operator=(const stack &origin) {
			m_con = origin.m_con;
			return *this;
		}

		bool empty() const { return this->m_con.empty(); }
		size_t size() const { return this->m_con.size(); }
		value_type top() { return this->m_con.back(); }
		const value_type top() const { return this->m_con.back(); }
		void push(const value_type &val) { this->m_con.push_back(val); }
		void pop() {this->m_con.pop_back(); }

		friend bool operator==(const stack &x, const stack &y) {
			return x.m_con == y.m_con;
		}
		friend bool operator!=(const stack &x, const stack &y) {
			return !(x == y);
		}
		friend bool operator<(const stack &x, const stack &y) {
			return x.m_con < y.m_con;
		}
		friend bool operator<=(const stack &x, const stack &y) {
			return !(x > y);
		}
		friend bool operator>(const stack &x, const stack &y) {
			return x.m_con < y.m_con;
		}
		friend bool operator>=(const stack &x, const stack &y) {
			return !(x < y);
		}
	};
}

#endif