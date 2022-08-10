#ifndef TREE_HPP
# define TREE_HPP

#include <iostream>
#include "./iterator.hpp"
#include "./utils.hpp"

#define NONE 0
#define LEFT 1
#define RIGHT 2
#define BOTH 3

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
		tree_node(const T &v) : value(v), parent(NULL), right(NULL), left(NULL) {}
		tree_node(const tree_node &origin) : value(origin.value), parent(origin.parent), right(origin.right), left(origin.left) {}
		~tree_node() {}

		tree_node &operator=(const tree_node &origin) {
			if (this != origin) {
				this->value = origin.value;
				this->parent = origin.parent;
				this->right = origin.right;
				this->left = origin.left;
			}
		}

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
		typedef T														pair_type;
		typedef T														value_type;
		typedef size_t													size_type;
		typedef std::ptrdiff_t											diff_type;
		typedef Compare													value_compare;
		typedef typename Alloc::template rebind<Node>::other			allocator_type; // what the hell is?
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef typename Node::node_pointer								node_pointer;
		typedef typename ft::tree_iterator<pair_type, Node>				iterator;
		typedef typename ft::tree_iterator<const pair_type, Node>		const_iterator;

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
			: m_alloc(alloc), m_size(origin.m_size), m_comp(origin.value_comp())
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
			return *this;
		}

		// iterator (const)
		iterator begin() {
			if (m_size == 0)
				return iterator(m_virtual);
			return iterator(get_min_node());
		}
		const_iterator begin() const {
			if (m_size == 0)
				return iterator(m_virtual);
			return iterator(get_min_node());
		}
		
		iterator end() { return iterator(m_virtual); }
		const_iterator end() const { return iterator(m_virtual); }

		// capacity
		bool empty() const { return (m_size == 0); }

		size_t size() const { return m_size; }

		size_t max_size() const {
			return std::min<size_t>(m_alloc.max_size(),
				std::numeric_limits<diff_type>::max());
		}

		// modifiers
		ft::pair<iterator, bool> insert(const pair_type &pair) // 삽입한 그 페어를 리턴
		{
			if (m_size == 0) {
				this->set_root(pair);
				return ft::pair<iterator, bool>(iterator(m_root), true);
			}
			ft::pair<node_pointer, int> pos = this->find_insert_position(m_root, pair);
			if (pos.second == NONE) // duplicated
				return ft::pair<iterator, bool>(iterator(pos.first), false);
			node_pointer new_node = m_alloc.allocate(1);
			// pos.first = m_alloc.allocate(1);
			m_alloc.construct(new_node, Node(pair)); // const
			new_node->set_parent(pos.first);
			new_node->set_left(NULL);
			new_node->set_right(NULL);
			if (pos.second == LEFT)
				(pos.first)->set_left(new_node);
			else
				(pos.first)->set_right(new_node);
			m_size++;
			this->rotate(pos.first);
			return ft::pair<iterator, bool>(iterator(new_node), true);
		}

		ft::pair<iterator, bool> insert(iterator position, const pair_type &pair)
		{
			if (m_size == 0) {
				set_root(pair);
				return ft::pair<iterator, bool>(iterator(m_root), true);
			}
			if (!m_comp((*position).first, pair.first) && !m_comp(pair.first, (*position).first))
				return ft::pair<iterator, bool>(position, false);
			else
				return insert(pair);
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
				delete_node_child1(current);
			else
				delete_node_child2(current);
			m_size--;
			rotate(it.get_node_pointer());
			return true;
		}
		bool erase(const pair_type &pair) { return erase(find(pair)); }
		void erase(iterator first, iterator last) {
			for (iterator it = first; it != last;)
				erase(it++);
		}

		void print_root(node_pointer _root)
		{
			if (m_size == 4) {
				std::cout << "m_virtual : " << m_virtual->value.first << std::endl;
				std::cout << "trip to m_vir : " << m_virtual->left->parent->value.first << std::endl;
				std::cout << "_root : " << _root->value.first << std::endl;
				std::cout << "trip to root : "
					<< _root->left->parent->right->right->parent->parent->value.first << std::endl;
				return ;
			}
			if (_root->left) {
				std::cout << "<- left : " << _root->left->value.first << " | ";
				print_root(_root->left);
			}
			if (_root->right) {
				std::cout << "-> right : " << _root->right->value.first << " | ";
				std::cout << "right->parent " << _root->right->parent->value.first << std::endl;
				print_root(_root->right);
			}
			std::cout << "\n";
		}

		void rotate(node_pointer p)
		{
			std::cout << "hi~ rotate fnc, size: " << m_size << "\n";
			if (m_size < 3)
				return ;
			if (p->parent)
			{
				node_pointer pparent = p->parent;
				while (pparent != m_virtual)
				{
					std::cout << "m_vir : " << m_virtual->right->parent->value.first << std::endl;
					std::cout << "vir->LR : " << m_virtual->left->value.first << ", " << m_virtual->right->value.first;
					std::cout << ", m_root :" << m_root->value.first << std::endl;
					print_root(m_root);

					ft::pair<int, int> left_node = get_height_balance(pparent->left);
					ft::pair<int, int> right_node = get_height_balance(pparent->right);
					int h_diff = left_node.first - right_node.first;
					// int b_diff = left_node.second - right_node.second;

					if (abs(h_diff) <= 1)
						return ;
					if (h_diff > 0) {
						if (left_node.second < 0)
							rotate_LR(pparent);
						else
							rotate_LL(pparent);
					}
					else {
						if (right_node.second > 0)
							rotate_RL(pparent);
						else
							rotate_RR(pparent);
					}

					pparent = pparent->parent;
				}
			}
		}

		ft::pair<node_pointer, int> get_LR(node_pointer stand)
		{
			if (stand == NULL)
				return ft::pair<node_pointer, int>(NULL, NONE);
			if (stand->parent->left == stand)
				return ft::pair<node_pointer, int>(stand, LEFT);
			else
				return ft::pair<node_pointer, int>(stand, RIGHT);
		}

		int get_LR_int(node_pointer stand)
		{
			if (stand == NULL)
				return NONE;
			if (stand->parent->right == stand && stand->parent->left == stand)
				return BOTH;
			if (stand->parent->left == stand)
				return LEFT;
			else
				return RIGHT;
		}

		void rotate_LL(node_pointer parent)
		{
			if (parent == m_virtual)
				return ;
			std::cout << "rotate LL : " << parent->value.first << std::endl;
			node_pointer pa_parent = parent->parent;
			if (!parent->left || !parent->left->left)
				return ;
			node_pointer center = parent->left;
			int LR = get_LR_int(parent);

			parent->left = center->right;
			if (center->right)
				center->right->parent = parent;

			center->parent = pa_parent; // something wrong
			parent->parent = center; // 아 씨
			center->right = parent;
			switch (LR)
			{
			case LEFT:
				parent->parent->right = center;
				std::cout << "left!\n";
				break;
			case RIGHT:
				parent->parent->left = center;
				std::cout << "right!\n";
				break;
			case BOTH:
				m_virtual->left = center;
				m_virtual->right = center;
				m_root = center;
				std::cout << "both!\n";
				break;
			case NONE:
				std::cout << "None!\n";
				std::range_error("No parent->parent");
				break;
			}
		}

		void rotate_RR(node_pointer parent)
		{
			if (parent == m_virtual)
				return ;
			std::cout << "rotate RR : " << parent->value.first << std::endl;
			if (!parent->right || !parent->right->right)
				return ;
			node_pointer center = parent->right;
			int LR = get_LR_int(parent);

			parent->right = center->left;
			if (center->left)
				center->left->parent = parent;

			center->parent = parent->parent;
			center->left = parent;
			parent->parent = center;
			switch (LR)
			{
			case LEFT:
				parent->parent->right = center;
				std::cout << "left!\n";
				break;
			case RIGHT:
				parent->parent->left = center;
				std::cout << "right!\n";
				break;
			case BOTH:
				m_virtual->left = center;
				m_virtual->right = center;
				m_root = center;
				std::cout << "both!\n";
				break;
			case NONE:
				std::cout << "None!\n";
				std::range_error("No parent->parent");
				break;
			}
		}

		void rotate_LR(node_pointer parent)
		{
			rotate_LL(parent);
			rotate_RR(parent);
		}

		void rotate_RL(node_pointer parent)
		{
			rotate_RR(parent);
			rotate_LL(parent);
		}

		void clear() {
			if (m_root)
				this->destroy(m_root);
			m_root = NULL;
			m_size = 0;
		}

		void swap(tree &sw) {
			node_pointer temp_virtual = m_virtual;
			node_pointer temp_root = m_root;
			size_t temp_size = m_size;

			m_virtual = sw.m_virtual;
			m_root = sw.m_root;
			m_size = sw.m_size;

			sw.m_virtual = temp_virtual;
			sw.m_root = temp_root;
			sw.m_size = temp_size;
		}

		value_compare &value_comp() { return m_comp; }
		const value_compare &value_comp() const { return m_comp; }

		iterator find(const pair_type &pair) {
			if (m_size == 0)
				return end();
			node_pointer np = m_root;
			while (np) {
				if (m_comp(pair.first, np->value.first))
					np = np->left;
				else if (!m_comp(np->value.first, pair.first))
					return iterator(np);
				else
					np = np->right;
			}
			return end();
		}
		const_iterator find(const pair_type &pair) const {
			if (m_size == 0)
				return end();
			node_pointer np = m_root;
			while (np) {
				if (m_comp(pair.first, np->value.first))
					np = np->left;
				else if (!m_comp(np->value.first, pair.first))
					return iterator(np);
				else
					np = np->right;
			}
			return end();
		}

		size_t count(const pair_type &pair) const { // 세는거 아님
			return !(find(pair) == end());
		}

		iterator lower_bound(const pair_type &pair) // 이상
		{
			node_pointer np = m_root;
			node_pointer result = m_virtual;

			while (np != NULL) {
				if (!m_comp(np->value.first, pair.first)) { // np->value < pair
					result = np;
					np = np->left;
				} else
					np = np->right;
			}
			return iterator(result);
		}
		const_iterator lower_bound(const pair_type &pair) const // 이상
		{
			node_pointer np = m_root;
			node_pointer result = m_virtual;

			while (np != NULL) {
				if (!m_comp(np->value.first, pair.first)) { // (less) np->value < pair
					result = np; // np->value >= [pair]
					np = np->left;
				} else
					np = np->right;
			}
			return const_iterator(result);
		}

		iterator upper_bound(const pair_type &pair) // 초과
		{
			node_pointer np = m_root;
			node_pointer result = m_virtual;

			while (np != NULL) {
				if (m_comp(pair.first, np->value.first)) {
					result = np; // [pair] < np->value
					np = np->left;
				} else
					np = np->right;
			}
			return iterator(result);
		}
		const_iterator upper_bound(const pair_type &pair) const // 초과
		{
			node_pointer np = m_root;
			node_pointer result = m_virtual;

			while (np != NULL) {
				if (m_comp(pair.first, np->value.first)) {
					result = np; // [pair] < np->value
					np = np->left;
				} else
					np = np->right;
			}
			return iterator(result);
		}

		ft::pair<iterator, iterator> equal_range(const pair_type pair) {
			return ft::pair<iterator, iterator>(lower_bound(pair), upper_bound(pair));
		}
		ft::pair<const_iterator, const_iterator> equal_range(const pair_type pair) const {
			return ft::pair<const_iterator, const_iterator>(lower_bound(pair), upper_bound(pair));
		}

	private:
		void set_root(const pair_type &pair)
		{
			m_root = m_alloc.allocate(1);
			m_alloc.construct(m_root, Node(pair));
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
				ptr->left = copy_tree(origin->left, ptr); // 재귀
				ptr->right = copy_tree(origin->right, ptr); // so cool
			}
			return ptr;
		}

		ft::pair<node_pointer, int> find_insert_position(node_pointer start, const pair_type &pair)
		{
			node_pointer current = start;
			node_pointer parent = start->parent;
			int child_flag;

			while (current)
			{
				parent = current;
				if (m_comp(pair.first, current->value.first)) { // 
					current = current->left;
					child_flag = LEFT;
				}
				else if (!m_comp(current->value.first, pair.first)) { // val == parent // why? .first
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
			int direction = get_LR_int(ptr);

			if (direction == LEFT)
				parent->left = NULL;
			else if (direction == RIGHT)
				parent->right = NULL;
			if (ptr == m_root) {
				m_root = NULL;
				m_virtual->left = NULL;
				m_virtual->right = NULL;
			}
			m_alloc.destroy(ptr);
			m_alloc.deallocate(ptr, 1);
		}

		void delete_node_child1(node_pointer ptr) // 1마리
		{
			node_pointer parent = ptr->parent;
			int direction = get_LR_int(ptr);
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

		void delete_node_child2(node_pointer ptr)
		{
			node_pointer parent = ptr->parent;
			int direction = get_LR_int(ptr);
			node_pointer prev_ptr = (--iterator(ptr)).get_node_pointer();
			int prev_direction = get_LR_int(prev_ptr);
			size_t prev_child_num = get_child_num(prev_ptr);

			if (direction == LEFT)
				parent->left = prev_ptr;
			if (direction == RIGHT)
				parent->right = prev_ptr;
			if (ptr == m_root) {
				m_root = prev_ptr;
				m_virtual->left = prev_ptr;
				m_virtual->right = prev_ptr;
			}
			// prev_ptr->parent = parent;
			if (prev_child_num == 0) { // easy
				if (prev_direction == LEFT)
					prev_ptr->parent->left = NULL;
				if (prev_direction == RIGHT)
					prev_ptr->parent->right = NULL;
			}
			else if (prev_child_num == 1) {
				node_pointer prev_child = prev_ptr->left;
				if (prev_child == NULL)
					prev_child = prev_ptr->right;
				
				if (prev_direction == LEFT)
					prev_ptr->parent->left = prev_child;
				if (prev_direction == RIGHT)
					prev_ptr->parent->right = prev_child;
				prev_child->parent = prev_ptr->parent;
			}
			prev_ptr->parent = parent;
			prev_ptr->left = ptr->left;
			if (ptr->left)
				ptr->left->parent = prev_ptr;
			prev_ptr->right = ptr->right;
			if (ptr->right)
				ptr->right->parent = prev_ptr;

			m_alloc.destroy(ptr);
			m_alloc.deallocate(ptr, 1);
		}

		void destroy(node_pointer ptr) {
			if (ptr) {
				destroy(ptr->left); // recursive (재귀)
				destroy(ptr->right);
				m_alloc.destroy(ptr);
				m_alloc.deallocate(ptr, 1);
			}
		}

		ft::pair<int, int> get_height_balance(node_pointer p)
		{
			if (p == 0)
				return ft::pair<int, int>(-1, -1);
			ft::pair<int, int> left_node = get_height_balance(p->left);
			ft::pair<int, int> right_node = get_height_balance(p->right);
			int height = std::max(left_node.first, right_node.first) + 1;
			int balance = left_node.first - right_node.first;
			return ft::pair<int, int>(height, balance);
		}
	};
};

#endif