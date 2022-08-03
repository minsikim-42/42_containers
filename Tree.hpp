#ifndef TREE_HPP
# define TREE_HPP

#include <iostream>
#include "Iterator.hpp"
#include "Utils.hpp"

#define NONE 0
#define LEFT 1
#define RIGHT 2

namespace ft
{
	template <typename T>
	struct tree_node
	{
		T			value;
		tree_node	*parent;
		tree_node	*right;
		tree_node	*left;

		tree_node() : parent(nullptr), right(nullptr), left(nullptr) {}
		~tree_node() {}

		void set_parent(tree_node *p) { parent = p; }
		void set_right(tree_node *p) { right = p; }
		void set_left(tree_node *p) { left = p; }
		void set_value(const T &val) { value.second = val.second; } // T가 뭔줄알고 .second를 쓰지
	};

	// AVL tree
	template <typename T, typename Compare,
			typename Node = ft::tree_node<T>,
			typename Alloc = std::allocator<Node> >
	class tree
	{
	public:
		typedef typename Alloc::template rebind<Node>::other	allocator_type; // what the hell is?
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename Node::node_pointer						node_pointer;
		typedef typename ft::tree_iterator<T, Node>				iterator;
		typedef typename ft::tree_iterator<const T, Node>		const_iterator;
		
	private:
		node_pointer	m_root;
		node_pointer	m_virtual;
		allocator_type	m_alloc;
		size_t			m_size;
		Compare			m_comp;

	public:
		tree(const Compare &comp, const allocator_type &alloc = allocator_type())
			: m_root(NULL), m_alloc(alloc), m_size(0), m_comp(comp)
		{
			m_virtual = m_alloc.allocate(1);
			m_alloc.construct(m_virtual, Node());
			m_virtual->parent = NULL;
			m_virtual->left = NULL;
			m_virtual->right = NULL;
		}
		tree(const tree &origin, const allocator_type &alloc = allocator_type())
			: m_alloc(alloc), m_size(origin.m_size()), m_comp(origin.m_comp())
		{
			m_virtual = m_alloc.allocate(1);
			m_alloc.construct(m_virtual, Node());
			m_root = copy_tree(origin.m_root, m_virtual); // 
			m_virtual->parent = NULL;
			m_virtual->left = m_root;
			m_virtual->right = m_root;
			if (m_root) {
				m_root->parent = m_virtual;
			}
		}

		~tree() {
			this->clear();
			m_alloc.destroy(m_virtual);
			m_alloc.deallocate(m_virtual, 1);
			m_virtual = NULL;
		}

		// operator=

		// iterator (const)
		iterator begin() {
			if (m_size == 0)
				return iterator(m_virtual);
			return iterator(get_min_node());
		}
		
		iterator end() { return iterator(m_virtual); }

		// capacity
		bool empty() const { return (m_size == 0); }

		size_t size() const { return m_size; }

		size_t max_size() const {
			return std::min<size_t>(m_alloc.max_size(),
				std::numeric_limits<T>::max());
		}

		ft::pair<iterator, bool> insert(const T &val) // 삽입한 그 페어를 리턴
		{
			if (m_size == 0) {
				this->set_root(val);
				return ft::pair<iterator, bool>(iterator(m_root, val));
			}
			ft::pair<node_pointer, int> pos = this->find_insert_position(m_root, val);
			if (pos.second == NONE) // duplicated
				return ft::pair<iterator, bool>(iterator(pos.first), false);
			node_pointer new_node = m_alloc.allocator(1);
			m_alloc.construct(new_node, Node(val));
			new_node->set_parent(pos.first);
			new_node->set_left(NULL);
			new_node->set_right(NULL);
			if (pos.second == LEFT)
				(pos.first)->set_left(new_node);
			else
				(pos.first)->set_right(new_node);
			m_size++;
			this->rotate();
		}

	private:
		void set_root(const T &val)
		{
			m_root = m_alloc.allocate(1);
			m_alloc.construct(m_root, Node());
			m_virtual->left = m_root;
			m_virtual->right = m_root;
			m_root->parent = m_virtual;
			m_root->left = NULL;
			m_root->right = NULL;
			m_size++;
		}

		node_pointer get_min_node() const
		{
			node_pointer temp = m_root;
			while (temp->left)
				temp = temp->left;
			return temp;
		}

		node_pointer copy_node(const Node &origin)
		{
			node_pointer ptr = m_alloc.allocate(1);

			m_alloc.construct(ptr, Node(origin.value));
			return ptr;
		}

		node_pointer copy_tree(node_pointer origin, node_pointer parent)
		{
			node_pointer ptr = NULL;
			if (origin)
			{
				ptr = copy_node(*origin);
				ptr->parent = parent;
				ptr->left = copy_tree(origin.left, ptr); // 재귀
				ptr->right = copy_tree(origin->right, ptr); // so cool
			}
			return ptr;
		}

		ft::pair<node_pointer, int> find_insert_position(node_pointer start, const T &val)
		{
			node_pointer current = start;
			node_pointer parent = start->parent;
			int child_flag;

			while (current)
			{
				parent = current;
				if (m_comp(val, current->value)) { // parent < val
					current = current->left;
					child_flag = LEFT;
				}
				else if (!m_comp(current->value, val)) { // val == parent
					return ft::pair<node_pointer, int>(current, NONE);
				}
				else {
					current = current->right; // val < parent
					child_flag = RIGHT;
				}
			}
			if (child_flag == LEFT)
				return ft::pair<node_pointer, int>(parent, LEFT);
			else
				return ft::pair<node_pointer, int>(parent, RIGHT);
		}

		ft::pair<int, int> get_height_balance(node_pointer p)
		{
			if (p == 0)
				return ft::pair<int, int>(-1, -1);
			ft::pair<int, int> left_node = get_height_balance(p->left);
			ft::pair<int, int> right_node = get_height_balance(p->right);
			int height = std::max(left_node.m_first, right_node.m_first) + 1;
			int balance = left_node.m_first - right_node.m_first;
			return ft::pair<int, int>(height, balance);
		}

		void rotate_LR() {
			rotate_RR();
		}

		void rotate_RL() {
			rotate_LL
		}

		void rotate()
		{
			if (m_size < 3)
				return ;
			ft::pair<int, int> left_node = get_height_balance(m_root->left);
			ft::pair<int, int> right_node = get_height_balance(m_root->right);
			int balance = left_node.m_first - right_node.m_first;
								//  height				balance
			if (abs(balance) <= 1) { // balance OK...?
				if (left_node.m_second < 0) // right big
					return retate_LR();
				else
					return retate_LL(m_root);
			}
			else { // balance NO
				if (right_node.m_second > 0) // left big
					return rotate_RL();
				else
					return rotate_RR(m_root);
			}
		}
	};
};

#endif