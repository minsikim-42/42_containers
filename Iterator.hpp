#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include <iostream>
// #include <iterator>

namespace ft
{
	// struct input_iterator_tag	{};		// IT Category -> std::
	// struct output_iterator_tag	{};
	// struct forward_iterator_tag			: public input_iterator_tag {}; // why?
	// struct bidirectional_iterator_tag	: public forward_iterator_tag {};
	// struct random_access_iterator_tag	: public bidirectional_iterator_tag {};



	template <							// IT traits
		typename Category,
		typename T,
		typename Distance = std::ptrdiff_t,
		typename Pointer = T*,
		typename Reference = T&
	>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <typename Iterator>		// IT traits
	struct iterator_traits
	{
		typedef typename Iterator::difference_type  	difference_type;
		typedef typename Iterator::value_type       	value_type;
		typedef typename Iterator::pointer          	pointer;
		typedef typename Iterator::reference        	reference;
		// typedef typename Iterator::iterator_category	iterator_category;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t            		difference_type;
		typedef T                         		value_type;
		typedef T*                        		pointer;
		typedef T&                        		reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t            		difference_type;
		typedef T                         		value_type;
		typedef const T*                  		pointer;
		typedef const T&                  		reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};



	template <class T>					// ft_IT
	class ft_iterator : public ft::iterator<std::random_access_iterator_tag, T> // why?
	{
	public :
		typedef typename ft::iterator_traits<T>::difference_type difference_type;
		typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<T>::pointer pointer;
		typedef typename ft::iterator_traits<T>::reference reference;
		typedef typename ft::iterator_traits<T>::value_type value_type;

	private :
		// typedef typename ft::iterator_traits<T>::pointer pos; // error!
		pointer m_pos;

	public :
		ft_iterator() : m_pos(nullptr) {};
		explicit ft_iterator(pointer p) : m_pos(p) {};
		// template <typename U>
		// ft_iterator(const ft_iterator<U>& iter) : m_pos(iter.base()) {};

		pointer base() const { return this->m_pos; } // why? what is base?

		// operator=
		template <typename U>
		ft_iterator<U> &operator=(const ft_iterator<U> &origin)
		{
			m_pos = origin.base();

			return *this;
		}
		// operator* -> + += - -= ++ -- []
		reference operator*(void) const
		{
			return *(this->m_pos);
		}
		pointer operator->() const
		{
			return &(this->operator*());
		}
		ft_iterator operator+(difference_type n) const
		{
			ft_iterator temp(*this);
			temp += n;
			return temp;
		}
		ft_iterator &operator+=(difference_type n)
		{
			return this->m_pos + n;
		}
	};
	// operator == != < > >= <= - +

	
	template <class T>					// reverse_IT
	class reverse_iterator : ft::iterator<std::random_access_iterator_tag, T>
	{
		typedef typename ft::iterator_traits<T>::difference_type difference_type;
		typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<T>::pointer pointer;
		typedef typename ft::iterator_traits<T>::reference reference;
		typedef T iterator_type;
		// typedef typename ft::iterator_traits<T>::value_type iterator_type;

	protected :
		iterator_type current; // why?

	public :
		reverse_iterator() {}
		explicit reverse_iterator(iterator_type p) : current(p) {}
		template <typename U>
		reverse_iterator(const reverse_iterator<U>& iter) : current(iter.bese()) {}

		iterator_type base() const { return this->current; }

		// operator=
		// operator* -> + += - -= ++ -- []
		// reverse_iterator operator+(const difference_type &n)
		// {
		// 	;
		// }
	};
	// operator== != > >= < <= - +

} // namespace ft


#endif