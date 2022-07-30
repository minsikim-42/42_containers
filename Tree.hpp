#ifndef TREE_HPP
# define TREE_HPP

#include <iostream>
#include "Iterator.hpp"

namespace ft
{
	template <typename T>
	struct tree_node
	{
		typedef T			node_value_type;
		typedef T*			node_value_type_pointer;
		typedef tree_node	node;
		typedef node*		node_pointer;

		node_value_type		value;
		node_pointer		parent;
		node_pointer		right;
		node_pointer		left;

		tree_node() : parent(NULL), right(NULL), left(NULL) {}
		~tree_node() {}

		void set_parent(node_pointer p) { parent = p; }
		void set_right(node_pointer p) { right = p; }
		void set_left(node_pointer p) { left = p; }
		void set_value(const node_value_type &val) { value.second = val.second; } // T가 뭔줄알고 .second를 쓰지
	};

	// AVL tree
	template <
				typename T,
				typename Compare,
				typename Node = ft::tree_node<T>,
				typename Alloc = std::allocator<Node>
	>
	class AVL
	{
	public:
		typedef T							value_type;
		typedef Compare						value_compare;
		typedef std::ptrdiff_t				difference_type;
		typedef typename Node::node_pointer	node_pointer;
		typedef typename ft::tree_iterator<value_type, Node>	iterator;
	
	private:
		node_pointer	_root;
		node_pointer	_super_root;
		// allocator_type	_alloc;
		size_t			_size;
		value_compare	_value_comp;
	};
};

#endif