#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include <iterator>

namespace ft
{
	struct input_iterator_tag {};		// IT Categori
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {}; // why?
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};



	template <							// IT
		typename Category,
		typename T,
		typename Distance = std::ptrdiff_t,
		typename Pointer = T*,
		typename Reference = T&
	>
	struct iterator {
		typedef T		value_type;
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
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t            	difference_type;
		typedef T                         	value_type;
		typedef T*                        	pointer;
		typedef T&                        	reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t            	difference_type;
		typedef T                         	value_type;
		typedef const T*                  	pointer;
		typedef const T&                  	reference;
		typedef random_access_iterator_tag	iterator_category;
	};



	template <typename T>
	class ft_iterator : ft::iterator<std::random_access_iterator_tag, T> // why?
	{
	private :
		typedef typename ft::iterator_traits<T>::pointer pos;

	public :
		typedef typename ft::iterator_traits<T>::difference_type difference_type;
		typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
		// typedef typename ft::iterator_traits<T>::iterator_traits iterator_traits; // ?
		typedef typename ft::iterator_traits<T>::pointer pointer;
		typedef typename ft::iterator_traits<T>::reference reference;
		typedef typename ft::iterator_traits<T>::value_type value_type;

		ft_iterator() : pos(nullptr) {};
		explicit ft_iterator(pointer p) : pos(p) {};

		pointer base() const { return this->pos; } // why? what is base?

		// operator=

		// operator* -> + += - -= ++ -- []
	};

	// operator == != < > >= <= - +

	// reverse
	// template <typename T>
	// class reverse_iterator : iterator<

} // namespace ft


#endif