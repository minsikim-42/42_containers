#ifndef TREE_HPP
# define TREE_HPP

#include <iostream>

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

		tree_node() : parent(nullptr), right(nullptr), left(nullptr) {}
		~tree_node() {}

		void set_parent(node_pointer p) { parent = p; }
		void set_right(node_pointer p) { right = p; }
		void set_left(node_pointer p) { left = p; }
		void set_value(const node_value_type &val) { value.second = val.second; } // T가 뭔줄알고 .second를 쓰지
	};
};

#endif