#ifndef ITERATOR_TPP
# define ITERATOR_TPP

#include <memory>
#include <iostream>
#include "./Iterator.hpp"

namespace ft
{
	template<typename T, typename allocator = std::allocator<T> >
	class vector
	{
	public :
		// std::allocator<T> allocator; // why?
		typedef T											value_type;
		typedef allocator									allocator_type;
		typedef typename allocator_type::pointer			pointer;
		// typedef ft::ft_iterator<value_type>					iterator;
		typedef ft::ft_iterator<pointer>					iterator;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;

	protected :
		pointer			m_pos;
		size_t			m_size;
		size_t			m_cap;
		allocator_type	m_alloc;

	private :


	public :
		// constructor
		// vector(void) :  m_pos(nullptr), m_size(0), m_cap(0), m_alloc(nullptr) {}
		explicit vector(const allocator_type& _alloc = allocator_type())
			: m_pos(nullptr), m_size(0), m_cap(0), m_alloc(_alloc) {}

		explicit vector(size_t _n)
			: m_pos(nullptr), m_size(_n), m_cap(_n)
		{
			m_pos = m_alloc.allocate(m_size);
		}

		// destructor
		virtual ~vector() 
		{
			this->clear();
			// m_alloc.deallocate(this->m_pos, this->capacity());
		}

		// begin & end
		iterator begin() {
			iterator temp(this->m_pos);
			return temp;
		}

		iterator end() {
			return iterator(m_pos + m_size);
		}

		// Capacity
		size_t size() const { return this->m_size; }
		size_t capacity() const { return this->m_cap; }
		bool empty() const { return (this->m_size == 0); }
		size_t max_size() const { return std::numeric_limits<size_t>::max() / sizeof(value_type); } // why /

		void resize(size_t _n, value_type _val = value_type()) // again
		{
			if (static_cast<size_t>(_n) > this->max_size())
				throw std::length_error("ft::vector");
			
			size_t si = this->size();
			if (_n > si)
			{
				size_t diff = _n - si;
				if (static_cast<size_t>(this->m_size - this->m_size) >= diff)
				{
					for (size_t i = 0; i < diff; i++, m_size++)
						m_alloc.construct(this->m_size, _val);
				}
				else
				{
					size_t temp_cap;
					if (this->capacity() == 0) { temp_cap = 1; }
					else if (this->capacity() * 2 > this->max_size()) { temp_cap = this->max_size(); }
					else { temp_cap = this->capacity() * 2; } // why * 2, what are you doing?

					size_t new_cap = _n > temp_cap ? _n : temp_cap;
					this->reserve(new_cap);
					for (size_t i = 0; i < diff; i++)
					{
						--m_size;
						m_alloc.destroy(this->m_size);
					}
				}
			}
			else if (si > _n)
			{
				size_t diff = si - _n;
				for (size_t i = 0; i < diff; i++)
				{
					--m_size;
					m_alloc.destroy(this->m_size);
				}
			}
		}

		void reserve(size_t new_cap)
		{
			std::cout << "*new_cap: " << new_cap << ", reserv= cap: " << m_cap << ", size: " << m_size << std::endl;
			if (new_cap > this->m_cap)
			{
				size_t	old_size = this->m_size;
				size_t	old_cap = this->m_cap;

				if (old_cap * 2 > new_cap)
					this->m_cap *= 2;
				else
					this->m_cap = new_cap;
				pointer temp = m_alloc.allocate(this->m_cap);
				for (size_t i = 0; i < this->m_size; i++) // not understand
				{
					m_alloc.construct(temp + i, m_pos[i]);
				}
				this->clear();
				this->m_size = old_size; // ???
				// m_alloc.deallocate(m_pos, old_cap); ???
				m_pos = temp;
			}
		}

		void push_back(const value_type &_val)
		{
			this->reserve(this->m_size + 1);
			m_alloc.construct(&this->m_pos[this->m_size], _val); // confuse &this->m_pos[this->m_size]
			this->m_size++;
		}

		// clear
		void clear()
		{
			for (size_t i = 0; i < this->m_size; i++)
			{
				m_alloc.destroy(this->m_pos + i);
			}
			m_alloc.deallocate(this->m_pos, this->m_cap);
		}

		reference operator[](size_t n)
		{
			if (this->size() < n)
				throw std::length_error("ft::vector");
			return *(this->m_pos + n);
		}
	};
}

#endif