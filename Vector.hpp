#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
#include "iterator.hpp"
#include "utils.hpp"

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
		typedef ft::ft_iterator<const value_type>			const_iterator;
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
		vector(const vector &origin) // 복사생성자
			: m_pos(nullptr), m_size(origin.m_size), m_cap(origin.m_cap), m_alloc(origin.m_alloc)
		{
			iterator it = origin.begin();
			m_pos = m_alloc.allocate(m_size);
			for (int i = 0; it != origin.end(); it++, i++)
			{
				m_alloc.construct(m_pos + i, *it);
			}
		}
		explicit vector(const allocator_type& _alloc)
			: m_pos(nullptr), m_size(0), m_cap(0), m_alloc(_alloc) {}

		explicit vector(size_type _n)
			: m_pos(nullptr), m_size(_n), m_cap(_n)
		{
			m_pos = m_alloc.allocate(m_size);
		}
		vector(size_type _n, const value_type &val, const allocator_type &_alloc = allocator_type()) :
			m_pos(nullptr), m_size(0), m_cap(0), m_alloc(_alloc)
		{
			if (_n > 0)
				this->assign(_n, val);
		}
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &_alloc = allocator_type())
			: m_pos(nullptr), m_size(0), m_cap(0), m_alloc(_alloc)
		{
			this->assign(first, last);
		}

		// destructor
		virtual ~vector() 
		{
			this->clear();
			if (m_size)
				m_alloc.deallocate(this->m_pos, 0);
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
			return reverse_iterator(this->end());
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(this->end());
		}
		reverse_iterator rend() {
			return reverse_iterator(this->begin());
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(this->begin());
		}

		// Capacity
		size_type size() const { return this->m_size; }
		size_type capacity() const { return this->m_cap; }
		bool empty() const { return (this->m_size == 0); }
		size_type max_size() const {
			return std::min<size_type>(
				m_alloc.max_size(),
				std::numeric_limits<difference_type>::max()
			);
		} // why /

		void resize(size_type _n, value_type _val = value_type()) // again
		{
			if ((_n) > this->max_size())
				throw std::length_error("ft::vector");
			if (_n == m_size)
				return ;
			
			if (_n > m_size)
			{
				this->reserve(_n);
				for (size_type i = m_size; i < _n; i++)
					m_alloc.construct(m_pos + i, _val);
				m_size = _n;
			}
			else // _n < this->_size
			{
				for (size_type i = m_size; i > _n; i--)
				{
					m_alloc.destroy(m_pos + i);
				}
				m_size = _n;
			}
		}

		void reserve(size_type new_cap)
		{
			// std::cout << "*new_cap: " << new_cap << ", reserv= cap: " << m_cap << ", size: " << m_size << std::endl;
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

		iterator insert(iterator it, const value_type &val) {
			size_type distance = static_cast<size_type>(std::distance(this->begin().base(), it.base()));
			size_type new_size = this->m_size + 1;
			if (distance < 0)
				throw std::length_error("ft::vector");
			if (m_cap == 0)
				reserve(1);
			else if (this->m_cap < new_size)
				this->reserve(m_cap * 2);
			for (size_type i = new_size; i > distance; i--) {
				m_alloc.construct(m_pos + i, m_pos[i - 1]);
				m_alloc.destroy(m_pos + i - 1);
			}
			m_pos[distance] = val;
			m_size = new_size;
			return iterator(m_pos + distance);
		}
		void	insert(iterator pos, size_type count, const value_type &val)
		{
			size_type distance = static_cast<size_type>(std::distance(this->begin().base(), pos.base()));

			if (distance < 0)
				throw std::out_of_range("ft::vector");
			if (m_cap <= m_size + count)
			{
				if (m_size * 2 < (m_size + count))
					reserve(m_size + count);
				else
					this->reserve(m_cap * 2);
			}
			for (size_type i = 0; i < count; i++)
				this->insert(this->begin() + distance + i, val);
		}
		template <typename InputIterator>
		void	insert (iterator pos,
						InputIterator first,
						InputIterator last,
						typename ft::enable_if<!
							ft::is_integral<InputIterator>::value, InputIterator
						>::type* = 0
		) {
			size_type distance = std::distance(this->begin().base(), pos.base());
			size_type count = std::distance(first.base(), last.base());
			if (distance < 0)
				throw std::out_of_range("ft::vector");
			if (distance < 0 || distance > this->m_size)
			{
				if (this->m_size * 2 < m_size + count)
					this->reserve(m_size + count);
				else
					this->reserve(m_size * 2);
			}
			for (size_type i = 0; i < count; i++)
			{
				this->insert(this->begin() + distance + i, *first);
				++first;
			}
		}

		iterator erase(iterator pos) {
			size_type distance = std::distance(this->begin().base(), pos.base());
			size_type new_size = m_size - 1;

			m_alloc.destroy(m_pos + distance);
			for (size_type i = distance; i < new_size; i++) {
				m_alloc.construct(m_pos + i, m_pos[i + 1]);
				m_alloc.destroy(m_pos + i - 1);
			}
			m_size = new_size;
			return iterator(this->begin() + distance);
		}
		iterator erase(iterator first, iterator last) {
			size_type distance = std::distance(this->begin().base(), first.base());
			size_type it_distance = std::distance(first.base(), last.base());

			for (size_type i = 0; i < it_distance; i++)
				this->erase(first);
			return iterator(this->begin() + distance);
		}

		// swap
		void	swap(vector &other) {
			pointer t_ptr;
			size_type t_size;
			size_type t_cap;
			allocator_type t_alloc;

			t_ptr = other.m_pos;
			t_size = other.m_size;
			t_cap = other.m_cap;
			t_alloc = other.m_alloc;

			other.m_pos = this->m_pos;
			other.m_size = this->m_size;
			other.m_cap = this->m_cap;
			other.m_alloc = this->m_alloc;

			this->m_pos = t_ptr;
			this->m_size = t_size;
			this->m_cap = t_cap;
			this->m_alloc = t_alloc;
		}

		// clear
		void clear()
		{
			for (size_type i = 0; i < this->m_size; i++)
			{
				m_alloc.destroy(this->m_pos + i);
			}
			m_size = 0;
			// m_alloc.deallocate(this->m_pos, this->m_cap);
		}

		const_reference operator[](size_type n) const {
			if (n >= m_size)
				throw std::out_of_range("ft::vector");
			return *(this->m_pos + n);
		}
		reference operator[](size_type n)
		{
			if (m_size < n)
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
		reference back() { return *(this->end() -1); }
		const_reference back() const { return *(this->end() - 1); }
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& left, const vector<T,Alloc>& right)
	{ return left.size() == right.size() && ft::equal(left.begin(), left.end(), right.begin()); }

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& left, const vector<T,Alloc>& right)
	{ return !(left == right); }

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& left, const vector<T,Alloc>& right)
	{ return ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()); }

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& left, const vector<T,Alloc>& right)
	{ return right < left; }

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& left, const vector<T,Alloc>& right)
	{ return !(left < right); }

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& left, const vector<T,Alloc>& right)
	{ return !(right < left); }

	// vactor ft::swap
	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{ x.swap(y); }

}

#endif