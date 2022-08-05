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
		typename pair_typeair_type,
		typename Distance = std::ptrdiff_t,
		typename Pointer = pair_typeair_type*,
		typename Reference = pair_typeair_type&
	>
	struct iterator {
		typedef pair_typeair_type			value_type;
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

	template <typename pair_typeair_type>
	struct iterator_traits<pair_typeair_type*>
	{
		typedef std::ptrdiff_t            		difference_type;
		typedef pair_typeair_type                         		value_type;
		typedef pair_typeair_type*                        		pointer;
		typedef pair_typeair_type&                        		reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <typename pair_typeair_type>
	struct iterator_traits<const pair_typeair_type*>
	{
		typedef std::ptrdiff_t            		difference_type;
		typedef pair_typeair_type                         		value_type;
		typedef const pair_typeair_type*                  		pointer;
		typedef const pair_typeair_type&                  		reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};



	template <class pair_typeair_type>					// ft_IT
	class ft_iterator : public ft::iterator<std::random_access_iterator_tag, pair_typeair_type> // why?
	{
	public :
		typedef ft::iterator<std::random_access_iterator_tag, pair_typeair_type>	iter_type;
		typedef typename ft::iterator_traits<iter_type>::difference_type difference_type;
		typedef typename ft::iterator_traits<iter_type>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<iter_type>::pointer pointer;
		typedef typename ft::iterator_traits<iter_type>::reference reference;
		typedef typename ft::iterator_traits<iter_type>::value_type value_type;

	private :
		// typedef typename ft::iterator_traits<T>::pointer pos; // error!
		pointer m_pos;

	public :
		ft_iterator() : m_pos(nullptr) {};
		explicit ft_iterator(pointer p) : m_pos(p) {};
		// template <typename U>
		// ft_iterator(const ft_iterator<U>& iter) : m_pos(iter.base()) {};

		pointer base() const { return this->m_pos; } // why? what is base?

		operator ft_iterator<const value_type> () const { // conversion
			return ft_iterator<const value_type>(this->m_pos);
		}

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
			ft_iterator temp(m_pos + n);
			return temp;
		}
		ft_iterator &operator+=(difference_type n)
		{
			m_pos += n;
			return *this;
		}
		ft_iterator &operator-(difference_type n)
		{
			m_pos += n;
			return *this;
		}
		ft_iterator &operator-=(difference_type n)
		{
			m_pos += n;
			return *this;
		}
		ft_iterator &operator++() // ++it
		{
			++m_pos;
			return *this;
		}
		ft_iterator operator++(int) // it++
		{
			ft_iterator temp(*this);
			m_pos++;
			return temp;
		}
		ft_iterator &operator--() // --it
		{
			--m_pos;
			return *this;
		}
		ft_iterator &operator--(int) // it--
		{
			m_pos++;
			return *this;
		}
		reference operator[](size_t n) // it[n]
		{
			return *(*this + n);
		}
	};

	// operator == != < > >= <= - +
	// Non-member function Operators

	template <typename IT1, typename IT2>
	bool operator==(const ft_iterator<IT1> &x, const ft_iterator<IT2> &y) {
		return (x.base() == y.base());
	}
	template <typename IT1, typename IT2>
	bool operator!=(const ft_iterator<IT1> &x, const ft_iterator<IT2> &y) {
		return !(x == y);
	}
	template <class Iter1, class IT2>
	bool operator<(const ft_iterator<Iter1>& left, const ft_iterator<IT2>& right)
	{ return left.base() < right.base(); }

	template <class IT1, class IT2>
	bool operator>(const ft_iterator<IT1>& left, const ft_iterator<IT2>& right)
	{ return (right < left); }

	template <class IT1, class IT2>
	bool operator>=(const ft_iterator<IT1>& left, const ft_iterator<IT2>& right)
	{ return !(left < right); }

	template <class IT1, class IT2>
	bool operator<=(const ft_iterator<IT1>& left, const ft_iterator<IT2>& right)
	{ return !(right < left); }

	template <class Iter>
	ft_iterator<Iter> operator+ (
			typename ft_iterator<Iter>::difference_type n, ft_iterator<Iter> vi)
	{ vi += n; return vi; }

	template <class IT1, class IT2>
	typename ft_iterator<IT1>::difference_type operator- (
			const ft_iterator<IT1>& left, const ft_iterator<IT2>& right)
	{ return left.base() - right.base(); }



	template <class pair_typeair_type>					// reverse_IT
	class reverse_iterator : public ft::iterator<std::random_access_iterator_tag, pair_typeair_type>
	{
		typedef ft::iterator<std::random_access_iterator_tag, pair_typeair_type>	iter_type;
		typedef typename ft::iterator_traits<iter_type>::difference_type difference_type;
		typedef typename ft::iterator_traits<iter_type>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<iter_type>::pointer pointer;
		typedef typename ft::iterator_traits<iter_type>::reference reference;
		typedef pair_typeair_type iterator_type;
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


	// tree_iterator

	template <typename pair_typeair_type, typename NodeType, typename DiffType = std::ptrdiff_t>
	class tree_iterator : public iterator<std::bidirectional_iterator_tag, pair_typeair_type, DiffType> // why? bidirectional?
	{
	public:
		typedef NodeType							node_type;
		typedef typename node_type::node_pointer	node_pointer;

	private:
		node_pointer ptr;

	public:
		typedef iterator<std::bidirectional_iterator_tag, pair_typeair_type>			iter_type;
		typedef typename iterator_traits<iter_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iter_type>::value_type			value_type;
		typedef typename iterator_traits<iter_type>::difference_type	difference_type;
		typedef typename iterator_traits<iter_type>::pointer			pointer;
		typedef typename iterator_traits<iter_type>::reference			reference;

		// con , des
		tree_iterator() : ptr(NULL) {}
		tree_iterator(const tree_iterator &tree_it) : ptr(tree_it.get_node_pointer()) {}
		explicit tree_iterator(node_pointer p) : ptr(p) {}

		// operator
		// operator* -> ++ ==
		reference operator*() const { return ptr->value; }
		pointer operator->() const { return &(this->operator*()); } // &(this->operator*())

		// friend operator?

		node_pointer get_node_pointer() const { return ptr; }

	private:
		node_pointer next(node_pointer p) // there is super node(end node)!!!
		{
			if (p->parent == NULL) { // when p is super node(end node)
				return p;
			}
			if (p->right != NULL) {
				p = p->right;
				while (p->left != NULL)
					p = p->left;
				return p;
			}
			while (p != p->parent->left)
				p = p->parent;
			return p->parent;
		}

		node_pointer prev(node_pointer p)
		{
			if (p->parent == NULL) {
				while (p->right != NULL)
					p = p->right;
				return p;
			}
			if (p->left != NULL) {
				p = p->left;
				while (p->right != NULL)
					p = p->right;
				return p;
			}
			while (p != p->parent->right)
				p = p->parent;
			return p->parent;
		}

	};

} // namespace ft


#endif