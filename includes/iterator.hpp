#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include <iostream>
// #include <iterator>

namespace ft
{
	template <							// IT traits
		typename Category,
		typename Iterator,
		typename Distance = std::ptrdiff_t,
		typename Pointer = Iterator*,
		typename Reference = Iterator&
	>
	struct iterator {
		typedef Iterator			value_type;
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

	template <typename Iterator>
	struct iterator_traits<Iterator*>
	{
		typedef std::ptrdiff_t            		difference_type;
		typedef Iterator                         		value_type;
		typedef Iterator*                        		pointer;
		typedef Iterator&                        		reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
	template <typename Iterator>
	struct iterator_traits<const Iterator*>
	{
		typedef std::ptrdiff_t            		difference_type;
		typedef Iterator                         		value_type;
		typedef const Iterator*                  		pointer;
		typedef const Iterator&                  		reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};



	template <class Iterator>					// ft_IT
	class ft_iterator : public ft::iterator<std::random_access_iterator_tag, Iterator>
	{
	public :
		typedef ft::iterator<std::random_access_iterator_tag, Iterator>		iter_type;
		typedef typename ft::iterator_traits<iter_type>::difference_type	difference_type;
		typedef typename ft::iterator_traits<iter_type>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<iter_type>::pointer			pointer;
		typedef typename ft::iterator_traits<iter_type>::reference			reference;
		typedef typename ft::iterator_traits<iter_type>::value_type			value_type;

	private :
		// typedef typename ft::iterator_traits<T>::pointer pos; // error!
		pointer m_pos;

	public :
		ft_iterator() : m_pos(NULL) {};
		explicit ft_iterator(pointer p) : m_pos(p) {};
		template <typename U>
		ft_iterator(const ft_iterator<U> &iter) : m_pos(iter.base()) {};

		pointer base() const { return this->m_pos; }

		operator ft_iterator<const value_type> () const { // conversion
			return ft_iterator<const value_type>(this->m_pos);
		}

		// operator=
		ft_iterator &operator=(const ft_iterator &origin)
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
		ft_iterator operator-(difference_type n) const
		{
			return ft_iterator(m_pos - n);
		}
		ft_iterator &operator-=(difference_type n)
		{
			m_pos -= n;
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
		ft_iterator operator--(int) // it--
		{
			ft_iterator temp(*this);
			m_pos--;
			return temp;
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
	ft_iterator<Iter> operator+(
			typename ft_iterator<Iter>::difference_type n, const ft_iterator<Iter> &vi)
	{ return ft_iterator<Iter>(vi.base() + n); }

	template <class IT1, class IT2>
	typename ft_iterator<IT1>::difference_type operator- (
			const ft_iterator<IT1>& left, const ft_iterator<IT2>& right)
	{ return left.base() - right.base(); }


	// reverse_IT
	template <typename T>
	class reverse_iterator : public ft::iterator<std::random_access_iterator_tag, T>
	{
	public:
		typedef	T																iterator_type;
		// typedef ft::iterator<std::random_access_iterator_tag, T>				iter_type;
		typedef typename ft::iterator_traits<T>::difference_type		difference_type;
		typedef typename ft::iterator_traits<T>::iterator_category		iterator_category;
		typedef typename ft::iterator_traits<T>::pointer				pointer;
		typedef typename ft::iterator_traits<T>::reference				reference;
		// typedef typename ft::iterator_traits<T>::value_type iterator_type;

		iterator_type base() const { return this->current; }

	protected :
		iterator_type current;

	public :
		reverse_iterator() {}
		explicit reverse_iterator(iterator_type iter) : current(iter) {}
		template <typename U>
		reverse_iterator(const reverse_iterator<U>& iter) : current(iter.base()) {}


		// operator=
		template <typename U>
		reverse_iterator &operator=(const reverse_iterator<U> &rev) {
			current = rev.base();
			return *this;
		}
		// operator* -> + += - -= ++ -- []
		reference operator*() const { iterator_type temp = current; return *--temp; }
		pointer operator->() const { return &(operator*()); }
		reverse_iterator& operator++() { --current; return *this; }
		reverse_iterator operator++(int) { reverse_iterator temp(*this); --current; return temp; }
		reverse_iterator& operator--() { ++current; return *this; }
		reverse_iterator operator--(int) { reverse_iterator temp(*this); ++current; return temp; }
		reverse_iterator& operator+=(difference_type n) { current -= n; return *this; }
		// ft_iterator operator+(difference_type n) const
		// {
		// 	ft_iterator temp(m_pos + n);
		// 	return temp;
		// }
		reverse_iterator operator+(const difference_type &n) const
		{
			reverse_iterator temp(current - n);
			return temp;
		}
		reverse_iterator& operator-=(difference_type n) { current += n; return *this; }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }
		reference operator[](difference_type n) const { return *(*this + n); }
	};
	// operator== != > >= < <= - +
	template <typename Iter1, typename Iter2>
	bool operator==(const reverse_iterator<Iter1> &left, const reverse_iterator<Iter2> &right)
	{ return left.base() == right.base(); }

	template <typename Iter1, typename Iter2>
	bool operator!=(const reverse_iterator<Iter1> &left, const reverse_iterator<Iter2> &right)
	{ return left.base() != right.base(); }

	template <typename Iter1, typename Iter2>
	bool operator<(const reverse_iterator<Iter1> &left, const reverse_iterator<Iter2> &right)
	{ return left.base() > right.base(); }

	template <typename Iter1, typename Iter2>
	bool operator<=(const reverse_iterator<Iter1> &left, const reverse_iterator<Iter2> &right)
	{ return left.base() >= right.base(); }

	template <typename Iter1, typename Iter2>
	bool operator>(const reverse_iterator<Iter1> &left, const reverse_iterator<Iter2> &right)
	{ return left.base() < right.base(); }

	template <typename Iter1, typename Iter2>
	bool operator>=(const reverse_iterator<Iter1> &left, const reverse_iterator<Iter2> &right)
	{ return left.base() <= right.base(); }

	template <typename Iter>
	reverse_iterator<Iter> operator+(
			typename reverse_iterator<Iter>::difference_type n,
			const reverse_iterator<Iter> &rev_it)
	{ return reverse_iterator<Iter>(rev_it.base() - n); }

	template <typename Iter1, typename Iter2>
	typename reverse_iterator<Iter1>::difference_type operator-(
			const reverse_iterator<Iter1> &left,
			const reverse_iterator<Iter2> &right)
	{ return right.base() - left.base(); }

	// tree_iterator

	template <typename Iterator, typename NodeType, typename DiffType = std::ptrdiff_t>
	class tree_iterator : public iterator<std::bidirectional_iterator_tag, Iterator, DiffType>
	{
	public:
		typedef NodeType							node_type;
		typedef typename node_type::node_pointer	node_pointer;

	private:
		node_pointer ptr;

	public:
		typedef iterator<std::bidirectional_iterator_tag, Iterator>		iter_type;
		typedef typename iterator_traits<iter_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iter_type>::value_type			value_type;
		typedef typename iterator_traits<iter_type>::difference_type	difference_type;
		typedef typename iterator_traits<iter_type>::pointer			pointer;
		typedef typename iterator_traits<iter_type>::reference			reference;

		// con , des
		tree_iterator() : ptr(NULL) {}
		tree_iterator(const tree_iterator &tree_it) : ptr(tree_it.get_node_pointer()) {}
		explicit tree_iterator(node_pointer np) : ptr(np) {}
		~tree_iterator() {}

		// conversion operator
		operator tree_iterator<const value_type, node_type>() const {
			return tree_iterator<const value_type, node_type>(this->ptr);
		}
		// operator* -> ++ -- ==
		reference operator*() const { return ptr->value; }
		pointer operator->() const { return &(this->operator*()); } // &(this->operator*())
		tree_iterator &operator++() {
			ptr = this->next(ptr);
			return *this;
		}
		tree_iterator operator++(int) {
			tree_iterator temp(*this);
			ptr = this->next(ptr);
			return temp;
		}
		tree_iterator &operator--() {
			ptr = this->prev(ptr);
			return *this;
		}
		tree_iterator operator--(int) {
			tree_iterator temp(*this);
			ptr = this->prev(ptr);
			return temp;
		}

		// friend operator?
		friend bool operator==(const tree_iterator& x, const tree_iterator& y)
		{return x.ptr == y.ptr;}
		friend bool operator!=(const tree_iterator& x, const tree_iterator& y)
		{return !(x == y);}

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