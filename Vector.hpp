#ifndef ITERATOR_TPP
# define ITERATOR_TPP

#include <memory>
#include <iostream>

namespace ft
{
	template<typename T, typename allocator = std::allocator<T> >
	class vector
	{
	public :
		// std::allocator<T> allocator; // why?
		typedef T									value_type;
		typedef allocator							allocator_type;
		typedef std::size_t							size_type; // why?
		typedef typename allocator_type::pointer	pointer;

	protected :
		pointer			m_begin;
		pointer			m_end;
		pointer			m_end_cap;
		allocator_type	m_alloc;

	private :


	public :
		// constructor
		explicit vector(const allocator_type& _alloc = allocator_type())
			: m_begin(nullptr), m_end(nullptr), m_end_cap(nullptr), m_alloc(_alloc) {}

		explicit vector(size_type _n, const value_type &_val = value_type(), const allocator_type &_alloc = allocator_type())
			: m_begin(nullptr), m_end(nullptr), m_end_cap(nullptr), m_alloc(_alloc)
		{
			if (_n > 0)
			{
				if (static_cast<size_type>(_n) > this->max_size()) // why
					throw std::length_error("ft::vector");
				this->m_begin = this->m_end = this->m_alloc.allocate(_n);
				this->m_end_cap = this->m_begin + _n;
				for (size_type i = 0; i < _n; m_end++)
				{
					this->m_alloc.construct(this->m_end, _val); // why unknown
				}
			}
		}

		// destructor
		virtual ~vector() 
		{
			this->clear();
			m_alloc.deallocate(this->m_begin, this->capacity());
		}

		// Capacity
		size_type size() const { return static_cast<size_type>(this->m_end - this->m_begin); }
		size_type capacity() const { return static_cast<size_type>(this->m_end_cap - this->m_begin); }
		bool empty() const { return this->m_begin == this->m_end; }
		size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); } // why /

		void resize(size_type _n, value_type _val = value_type())
		{
			if (static_cast<size_type>(_n) > this->max_size())
				throw std::length_error("ft::vector");
			
			size_type si = this->size();
			if (_n > si)
			{
				size_type diff = _n - si;
				if (static_cast<size_type>(this->m_end_cap - this->m_end) >= diff)
				{
					for (size_type i = 0; i < diff; i++, m_end++)
						m_alloc.construct(this->m_end, _val);
				}
				else
				{
					size_type temp_cap;
					if (this->capacity() == 0) { temp_cap = 1; }
					else if (this->capacity() * 2 > this->max_size()) { temp_cap = this->max_size(); }
					else { temp_cap = this->capacity() * 2; } // why * 2

					diff = _n - this->size();
					size_type new_cap = _n > temp_cap ? _n : temp_cap;
					this->reserve(new_cap);
					for (size_type i = 0; i < diff; i++)
					{
						--m_end;
						m_alloc.destroy(this->m_end);
					}
				}
			}
			else if (si > _n)
			{
				size_type diff = si - _n;
				for (size_type i = 0; i < diff; i++)
				{
					--m_end;
					m_alloc.destroy(this->m_end);
				}
			}
		}

		void push_back(value_type &_val)
		{
			if (this->m_end == this->m_end_cap)
			{
				if (this->size() == this->max_size())
					throw std::length_error("ft::vector");
				
				size_type new_cap;
				if (this->capacity() == 0) { new_cap = 1; } // why what are you doing?
				else if (this->capacity() * 2 > this->max_size()) { new_cap = this->max_size(); }
				else { new_cap = this->capacity() * 2; } // why * 2
				this->reserve(new_cap);
			}
			m_alloc.construct(this->m_end, _val);
			m_end++;
		}

		// clear
		void clear()
		{
			size_type n = this->size();
			for (size_type i = 0; i < n; i++)
			{
				--m_end;
				m_alloc.destroy(this->m_end);
			}
		}
	};
}

#endif