#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
#include "Iterator.hpp"
#include "Utils.hpp"

namespace ft
{
	template<typename T, typename allocator = std::allocator<T> >
	class vector
	{
	public :
		// std::allocator<T> allocator; // why?
		typedef T											value_type;
		typedef allocator									allocator_type;
		typedef std::ptrdiff_t								difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		// typedef ft::ft_iterator<value_type>					iterator;
		typedef ft::ft_iterator<value_type>					iterator;
		typedef ft::ft_iterator<const value_type>				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	protected :
		pointer			m_pos;
		size_type		m_size;
		size_type		m_cap;
		allocator_type	m_alloc;

	private :


	public :
		// constructor
		vector(void) : m_pos(nullptr), m_size(0), m_cap(0) {}
		vector(const vector &origin)
			: m_pos(nullptr), m_size(0), m_cap(0), m_alloc(allocator_type()) { *this = origin; }
		explicit vector(const allocator_type& _alloc)
			: m_pos(nullptr), m_size(0), m_cap(0), m_alloc(_alloc) {}

		explicit vector(size_type _n)
			: m_pos(nullptr), m_size(_n), m_cap(_n)
		{
			m_pos = m_alloc.allocate(m_size);
		}

		// destructor
		virtual ~vector() 
		{
			this->clear();
			m_alloc.deallocate(this->m_pos, this->capacity());
		}

		// begin & end
		iterator begin() {
			iterator temp(this->m_pos);
			return temp;
		}
		const iterator begin() const {
			return iterator(this->m_pos);
		}

		iterator end() {
			return iterator(m_pos + m_size);
		}
		const iterator end() const {
			return iterator(m_pos + m_size);
		}
		reverse_iterator rbegin() {
			return reverse_iterator(m_pos + m_size);
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(m_pos + m_size);
		}
		reverse_iterator rend() {
			return reverse_iterator(m_pos);
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(m_pos);
		}

		// Capacity
		size_type size() const { return this->m_size; }
		size_type capacity() const { return this->m_cap; }
		bool empty() const { return (this->m_size == 0); }
		size_type max_size() const {
			return std::numeric_limits<size_type>::max() / sizeof(value_type);
		} // why /

		void resize(size_type _n, value_type _val = value_type()) // again
		{
			if ((_n) > this->max_size())
				throw std::length_error("ft::vector");
			
			size_type si = this->size();
			if (_n > si)
			{
				size_type diff = _n - si;
				if ((this->m_size - this->m_size) >= diff)
				{
					for (size_type i = 0; i < diff; i++, m_size++)
						m_alloc.construct(this->m_size, _val);
				}
				else
				{
					size_type temp_cap;
					if (this->capacity() == 0) { temp_cap = 1; }
					else if (this->capacity() * 2 > this->max_size()) { temp_cap = this->max_size(); }
					else { temp_cap = this->capacity() * 2; } // why * 2, what are you doing?

					size_type new_cap = _n > temp_cap ? _n : temp_cap;
					this->reserve(new_cap);
					for (size_type i = 0; i < diff; i++)
					{
						--m_size;
						m_alloc.destroy(this->m_size);
					}
				}
			}
			else if (si > _n)
			{
				size_type diff = si - _n;
				for (size_type i = 0; i < diff; i++)
				{
					--m_size;
					m_alloc.destroy(this->m_size);
				}
			}
		}

		void reserve(size_type new_cap)
		{
			std::cout << "*new_cap: " << new_cap << ", reserv= cap: " << m_cap << ", size: " << m_size << std::endl;
			if (new_cap > this->m_cap)
			{
				size_type	old_size = this->m_size;
				size_type	old_cap = this->m_cap;

				if (old_cap * 2 > new_cap)
					this->m_cap *= 2;
				else
					this->m_cap = new_cap;
				pointer temp = m_alloc.allocate(this->m_cap);
				for (size_type i = 0; i < this->m_size; i++) // not understand
				{
					m_alloc.construct(temp + i, m_pos[i]);
				}
				this->clear();
				this->m_size = old_size; // ???
				// m_alloc.deallocate(m_pos, old_cap); ???
				m_pos = temp;
			}
		}


		// modifire
		void assign(size_type n, const value_type &val)
		{
			// if (n > this->max_size())
			// 	throw std::length_error("ft::vector");
			// this->clear();
			// size_type cap = this->capacity();
			if (n <= m_cap)
			{
				this->clear();
				m_pos = m_alloc.allocate(m_cap);
				for (size_type i = 0; i < n; i++)
					m_alloc.construct(m_pos + i, val);
				m_size = n;
			}
			else // n > m_cap
			{
				pointer temp;
				size_type new_cap;
				if (m_cap == 0)
					new_cap = n;
				else
					new_cap = m_cap * 2; // cap 2배
				temp = m_alloc.allocate(new_cap); // 왜 clear를 미뤄두는거같지..?
				for (size_type i = 0; i < n; i++)
					m_alloc.construct(temp + i, val);
				this->clear();
				m_alloc.deallocate(m_pos, m_cap); ////// 임시 지움
				m_pos = temp;
				m_size = n;
				m_cap = new_cap;
			}
		}
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last, \
					typename ft::enable_if<! \
					ft::is_integral<InputIterator>::value \
					>::type* = NULL
		) {
			size_type new_size = static_cast<size_type>(std::distance(first, last));
			if (new_size <= 0)
				throw std::length_error("distance error");

			this->clear();
			if (new_size <= m_cap)
			{
				this->clear();
				for (size_type i = 0; i < new_size; i++)
					m_alloc.construct(m_pos + i, *(first++));
				m_size = new_size;
			}
			else
			{
				size_type new_cap;
				if (m_cap == 0)
					new_cap = new_size;
				else
					new_cap = m_cap * 2;
				pointer temp = m_alloc.allocate(new_cap);
				this->clear();
				m_alloc.deallocate(m_pos, m_cap); ///////// 임시 지움
				for (size_type i = 0; i < new_cap; i++)
					m_alloc.construct(temp + i, *(first++));
				m_pos = temp;
				m_size = new_size;
				m_cap = new_cap;
			}
		}

		// push & pop
		void push_back(const value_type &_val)
		{
			this->reserve(this->m_size + 1);
			m_alloc.construct(&this->m_pos[this->m_size], _val); // confuse &this->m_pos[this->m_size]
			this->m_size++;
		}
		void pop_back() {
			m_alloc.destroy(&this->m_pos[this->m_size]);
			this->m_size--;
		}

		iterator insert(iterator pos, const value_type &val) {
			size_type distance = static_cast<size_type>(std::distance(this->begin().base(), pos.base()));
			size_type new_size = this->m_size + 1;
			if (distance < 0)
				throw std::length_error("ft::vector");
			if (this->m_cap < new_size)
				this->reserve(m_cap * 2);
			for (size_type i = new_size; i > distance; i--) {
				m_alloc.construct(m_pos + i, m_pos[i - 1]);
				m_alloc.destroy(m_pos + i - 1);
			}
			m_pos[distance] = val;
			m_size = new_size;
			return iterator(m_pos + distance);
		}

		iterator erase(iterator pos) {
			size_type distance = static_cast<size_type>(std::distance(this->begin().base(), pos.base()));
			size_type new_size = m_size - 1;

			m_alloc.destroy(m_pos + distance);
			for (size_type i = distance; i < new_size; i++) {
				m_alloc.construct(m_pos + i, m_pos[i + 1]);
				m_alloc.destroy(m_pos + i - 1);
			}
			m_size = new_size;
		}

		// swap

		// clear
		void clear()
		{
			for (size_type i = 0; i < this->m_size; i++)
			{
				m_alloc.destroy(this->m_pos + i);
			}
			// m_alloc.deallocate(this->m_pos, this->m_cap);
		}

		const_reference operator[](size_type n) const {
			if (n >= this->size())
				throw std::out_of_range("ft::vecor");
			return *(this->m_pos + n);
		}
		reference operator[](size_type n)
		{
			if (this->size() < n)
				throw std::out_of_range("ft::vector");
			return *(this->m_pos + n);
		}

		reference at(size_type n)
		{
			if (n >= m_size || n < 0)
				throw std::out_of_range("ft::vector");
			return this->m_pos[n];
		}
		const_reference at(size_type n) const {
			if (n >= m_size || n < 0)
				throw std::out_of_range("ft::vector");
			return this->m_pos[n];
		}

		reference front() { return *(this->begin()); }
		const_reference front() const { return *(this->begin()); }
		reference back() { return *(this->end()); }
		const_reference back() const { return *(this->end()); }
	};
}

#endif