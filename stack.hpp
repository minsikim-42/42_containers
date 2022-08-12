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
		typedef size_t		size_type;
	
	protected:
		container_type		c;
	
	public:
		explicit stack(const container_type &container = container_type()) : c(container) {}
		stack(const stack &origin) : c(container_type(origin)) {}
		~stack() {}

		stack &operator=(const stack &origin) {
			c = container_type(origin);
			return *this;
		}

		bool empty() const { return this->c.empty(); }
		size_t size() const { return this->c.size(); }
		value_type &top() { return this->c.back(); }
		const value_type &top() const { return this->c.back(); }
		void push(const value_type &val) { this->c.push_back(val); }
		void pop() {this->c.pop_back(); }

		friend bool operator==(const stack &x, const stack &y) {
			return x.c == y.c;
		}
		friend bool operator!=(const stack &x, const stack &y) {
			return !(x == y);
		}
		friend bool operator<(const stack &x, const stack &y) {
			return x.c < y.c;
		}
		friend bool operator<=(const stack &x, const stack &y) {
			return !(x > y);
		}
		friend bool operator>(const stack &x, const stack &y) {
			return x.c > y.c;
		}
		friend bool operator>=(const stack &x, const stack &y) {
			return !(x < y);
		}
	};
}

#endif