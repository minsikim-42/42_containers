#ifndef TREE_HPP
# define TREE_HPP

#include <iostream>
#include "iterator.hpp"
#include "utils.hpp"

#define NONE 0
#define LEFT 1
#define RIGHT 2

namespace ft
{
	template <typename T>
	struct tree_node
	{
		typedef tree_node*	node_pointer;

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
		tree &operator=(const tree &t) {
			if (this != &t) {
				clear();
				m_root = copy_tree(t.m_root, m_virtual);
				m_virtual->parent = NULL;
				m_virtual->left = m_root;
				m_virtual->right = m_root;
				if (m_root)
					m_root->parent = m_virtual;
				m_size = t.m_size;
			}
		}

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
			return ft::pair<iterator, bool>(iterator(new_node), true);
		}

		ft::pair<iterator, bool> insert(iterator position, const T &val)
		{
			if (m_size == 0) {
				set_root(val);
				return ft::pair<iterator, bool>(iterator(m_root), true);
			}
			if (!m_comp(*position, val) && !m_comp(val, *position))
				return ft::pair<iterator, bool>(position, false);
			else
				return insert(val);
		}

		bool erase(iterator it)
		{
			if (m_size == 0 || it == end())
				return false;

			node_pointer current = it.get_node_pointer();
			size_t child_num = get_child_num(current);

			if (child_num == 0)
				delete_alone_node(current);
			else if (child_num == 1)
				delete_node_with_child1(current);
			else
				delete_node_with_child2(current);
			m_size--;
			rotate();
			return true;
		}

		void clear() {
			if (m_root)
				this->destroy(m_root);
			m_root = NULL;
			m_size = 0;
		}

	private:
		void set_root(const T &val)
		{
			m_root = m_alloc.allocate(1);
			m_alloc.construct(m_root, Node(val));
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

		size_t get_child_num(node_pointer ptr)
		{
			size_t child = 0;

			if (ptr->left)
				child++;
			if (ptr->right)
				child++;
			return child;
		}

		void delete_alone_node(node_pointer ptr)
		{
			node_pointer parent = ptr->parent;
			ft::pair<node_pointer, int> direction = get_LR(ptr);

			if (direction.m_second == LEFT)
				parent->left = NULL;
			else if (direction.m_second == RIGHT)
				parent->right = NULL;
			if (ptr == m_root) {
				m_root = NULL;
				m_virtual->left = NULL;
				m_virtual->right = NULL;
			}
			m_alloc.destroy(ptr);
			m_alloc.deallocate(ptr, 1);
		}

		void delete_node_with_child1(node_pointer ptr) // 1마리
		{
			node_pointer parent = ptr->parent;
			ft::pair<node_pointer, int> direction = get_LR(ptr);
			node_pointer child;

			if (!ptr->right)
				child = ptr->left; // left first
			else
				child = ptr->right;
			if (direction == LEFT)
				parent->left = child;
			if (direction == RIGHT)
				parent->right = child;
			if (ptr == m_root) {
				m_root = child;
				m_virtual->left = child;
				m_virtual->right = child;
			}
			child->parent = parent;

			m_alloc.destroy(ptr);
			m_alloc.deallocate(ptr, 1);
		}

		void delete_node_withh_child2(node_pointer ptr)
		{
			node_pointer parent = ptr->parent;
			ft::pair<node_pointer, int> direction = get_LR(ptr);
			node_pointer prev_ptr = (--iterator(ptr)).get_node_pointer();
			ft::pair<node_pointer, int> prev_direction = get_LR(prev_ptr);
			size_t prev_child_num = get_child_num(prev_ptr);

			if (direction.m_second == LEFT)
				parent->left = prev_ptr;
			if (direction.m_second == RIGHT)
				parent->right = prev_ptr;
			if (ptr == m_root) {
				m_root = prev_ptr;
				m_virtual->left = prev_ptr;
				m_virtual->right = prev_ptr;
			}
			// prev_ptr->parent = parent;
			if (prev_child_num == 0) {
				if (prev_direction.m_second == LEFT)
					prev_ptr->parent->left = NULL;
				if (prev_direction.m_second == RIGHT)
					prev_ptr->parent->right = NULL;
			}
			else if (prev_child_num == 1) {
				node_pointer prev_child = prev_ptr->left;
				if (prev_child == NULL)
					prev_child = prev_ptr->right;
				
				if (prev_direction.m_second == LEFT)
					prev_ptr->parent->left = prev_child;
				if (prev_direction.m_second == RIGHT)
					prev_ptr->parent->right = prev_child;
				prev_child->parent = prev_ptr->parent;
			}
			//
		}

		void destroy(node_pointer ptr) {
			if (ptr) {
				destroy(ptr->left); // recursive (재귀)
				destroy(ptr->right);
				m_alloc.destroy(ptr);
				m_alloc.dealloc(ptr, 1);
			}
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

		ft::pair<node_pointer, int> get_LR(node_pointer stand)
		{
			if (stand == NULL)
				return ft::pair<node_pointer, int>(NULL, NONE);
			if (stand->parent->left == stand)
				return ft::pair<node_pointer, int>(stand->parent, LEFT);
			else
				return ft::pair<node_pointer, int>(stand->parent, RIGHT);
		}

		void rotate_LL(node_pointer standard)
		{
			node_pointer parent = standard->parent;
			node_pointer S_left = standard->left;
			node_pointer S_right = standard->right;
			ft::pair<node_pointer, int> P_parent = get_LR(parent);

			parent->left = S_right;
			S_right->parent = parent;

			standard->right = parent;
			parent->parent = standard;

			if (P_parent.m_second == LEFT) {
				standard->parent = P_parent.m_first;
				P_parent.m_first->left = standard;
			}
			else {
				standard->parent = P_parent.m_first;
				P_parent.m_first->right = standard;
			}
		}

		void rotate_RR(node_pointer standard)
		{
			node_pointer parent = standard->parent;
			node_pointer S_left = standard->left;
			node_pointer S_right = standard->right;
			ft::pair<node_pointer, int> P_parent = get_LR(parent);

			parent->right = S_left;
			S_left->parent = parent;

			standard->left = parent;
			parent->parent = standard;

			if (P_parent.m_second == LEFT) {
				standard->parent = P_parent.m_first;
				P_parent.m_first->left = standard;
			}
			else {
				standard->parent = P_parent.m_first;
				P_parent.m_first->right = standard;
			}
		}

		void rotate_LR(node_pointer standard)
		{
			node_pointer parent = standard->parent;
			node_pointer R_child = standard->right;
			ft::pair<node_pointer, int> P_parent = get_LR(parent);

			standard->right = R_child->left;
			R_child->left->parent = standard;

			parent->left = R_child->right;
			R_child->right->parent = parent; // A node & C node

			R_child->left = standard;
			standard->parent = R_child;

			R_child->right = parent;
			parent->parent = R_child; // A - B - C

			if (P_parent.m_second == LEFT) {
				standard->parent = P_parent.m_first;
				P_parent.m_first->left = standard;
			}
			else {
				standard->parent = P_parent.m_first;
				P_parent.m_first->right = standard;
			}
		}

		void rotate_RL(node_pointer standard)
		{
			node_pointer parent = standard->parent;
			node_pointer L_child = standard->left;
			ft::pair<node_pointer, int> P_parent = get_LR(parent);

			standard->left = L_child->right;
			L_child->right->parent = standard;

			parent->right = L_child->left;
			L_child->left->parent = parent; // A node & C node

			L_child->left = parent;
			parent->parent = L_child;

			L_child->right = standard;
			standard->parent = L_child; // A - B - C

			if (P_parent.m_second == LEFT) {
				standard->parent = P_parent.m_first;
				P_parent.m_first->left = standard;
			}
			else {
				standard->parent = P_parent.m_first;
				P_parent.m_first->right = standard;
			}
		}

		void rotate()
		{
			if (m_size < 3)
				return ;
			ft::pair<int, int> left_node = get_height_balance(m_root->left);
			ft::pair<int, int> right_node = get_height_balance(m_root->right);
			int h_diff = left_node.m_first - right_node.m_first;
			int b_diff = left_node.m_second - right_node.m_second;
			//  first : height		second : balance
			if (abs(h_diff) <= 1) // balance OK
				return ;
			else { // balance NO
				if (h_diff > 0) // left big
				{
					if (b_diff > 0)
						rotate_LR(m_root);
					else
						rotate_LL(m_root);
				}
				else {
					if (b_diff > 0)
						rotate_RL(m_root);
					else
						rotate_RR(m_root);
				}
			}
		}
	};
};

#endif