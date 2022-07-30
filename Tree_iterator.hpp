#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iostream>
#include "Iterator.hpp"
#include "Tree.hpp"

namespace ft
{
	template <typename T, typename NodeType, typename DiffType = std::ptrdiff_t>
	class tree_iterator : public iterator<std::bidirectional_iterator_tag, T, DiffType>
	{
	public:
		typedef NodeType							node_type;
		typedef typename node_type::node_pointer	node_pointer;

	private:
		node_pointer ptr;

	public:
		typedef iterator<std::bidirectional_iterator_tag, T>	iter_type;
		typedef typename iterator_traits<iter_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iter_type>::value_type			value_type;
		typedef typename iterator_traits<iter_type>::difference_type	difference_type;
		typedef typename iterator_traits<iter_type>::pointer			pointer;
		typedef typename iterator_traits<iter_type>::reference			reference;

		// con , des

		// operator

		node_pointer get_node_pointer() { return ptr; }

	private:
		node_pointer next(node_pointer p)
		{

		}
	};
}

#endif