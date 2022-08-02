#ifndef TREE_HPP
# define TREE_HPP

#include <iostream>

namespace ft
{
	template <typename T>
	struct tree_node
	{
		T			data;
		tree_node	*parent;
		tree_node	*right;
		tree_node	*left;

		tree_node() : parent(nullptr), right(nullptr), left(nullptr) {}
		~tree_node() {}

		void set_parent(tree_node p) { parent = p; }
		void set_right(tree_node p) { right = p; }
		void set_left(tree_node p) { left = p; }
		void set_value(const node_value_type &val) { value.second = val.second; } // T가 뭔줄알고 .second를 쓰지
	};

	// AVL tree
};

#endif