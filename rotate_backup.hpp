void rotate_LL(node_pointer standard)
		{
			node_pointer parent = standard->parent;
			// node_pointer S_left = standard->left;
			node_pointer S_right = standard->right;
			ft::pair<node_pointer, int> P_parent = get_LR(parent);

			parent->left = S_right;
			S_right->parent = parent;

			standard->right = parent;
			parent->parent = standard;

			if (P_parent.second == LEFT) {
				standard->parent = P_parent.first;
				P_parent.first->left = standard;
			}
			else {
				standard->parent = P_parent.first;
				P_parent.first->right = standard;
			}
		}

		void rotate_RR(node_pointer standard)
		{
			node_pointer parent = standard->parent;
			node_pointer S_left = standard->left;
			// node_pointer S_right = standard->right;
			// ft::pair<node_pointer, int> P_parent = get_LR(parent);

			parent->right = S_left;
			S_left->parent = parent;

			standard->left = parent;
			parent->parent = standard;

			standard->parent = m_virtual; //
			m_virtual->left = standard; //
			m_virtual->right = standard; //

			// if (P_parent.second == LEFT) {
			// 	standard->parent = P_parent.first;
			// 	P_parent.first->left = standard;
			// }
			// else {
			// 	standard->parent = P_parent.first;
			// 	P_parent.first->right = standard;
			// }
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

			if (P_parent.second == LEFT) {
				standard->parent = P_parent.first;
				P_parent.first->left = standard;
			}
			else {
				standard->parent = P_parent.first;
				P_parent.first->right = standard;
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

			if (P_parent.second == LEFT) {
				standard->parent = P_parent.first;
				P_parent.first->left = standard;
			}
			else {
				standard->parent = P_parent.first;
				P_parent.first->right = standard;
			}
		}