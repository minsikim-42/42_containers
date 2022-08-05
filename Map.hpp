#ifndef MAP_HPP
# define MAP_HPP

#include "tree.hpp"
#include "utils.hpp"

namespace ft
{
	template <typename Key, typename T,
			typename Compare = std::less<Key>,
			typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const Key, T>						value_type; // tree value type
		typedef Alloc										allocator_type;
		typedef std::ptrdiff_t								difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		class value_compare : public std::binary_function<value_type, value_type, bool> // why? who are you?
		{
			friend class map;	// map class can acc to compare private member

		protected:
			Compare m_comp;

			value_compare(Compare com) : m_comp(com) {}

		public:
			bool operator()(const value_type &x, const value_type &y) const {
				return m_comp(x.first, y.first);
			} // value_type => pair
		};

		// tree
		typedef typename ft::tree<value_type, Compare>			tree_type;
		typedef typename tree_type::iterator					iterator;
		typedef typename tree_type::const_iterator				const_iterator;
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:
		tree_type m_tree;

	public:
		explicit map(const Compare comp = Compare(), const allocator_type &alloc = allocator_type())
			: m_tree(Compare(comp), alloc) {}
		template <typename InputIterator>
		map(InputIterator first, InputIterator last,
			const Compare &comp = Compare(),
			const allocator_type &alloc = allocator_type()) : m_tree(Compare(comp), alloc)
		{
			InputIterator it;
			for (it = first; it != last; it++)
				m_tree.insert(*it);
		}

		map(const map &origin) : m_tree(origin.m_tree) {}

		~map() {}

		map &operator=(const map &origin) {
			if (this != &origin)
				m_tree = origin.m_tree;
			return *this;
		}

		// iterator
		iterator begin() { return iterator(m_tree.begin()); }
		const_iterator begin() const { return const_iterator(m_tree.begin()); }
		iterator end() { return iterator(m_tree.end()); }
		const_iterator end() const { return const_iterator(m_tree.end()); }

		reverse_iterator rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
		reverse_iterator rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

		// capa
		bool empty() const { return m_tree.empty(); }
		size_t size() const { return m_tree.size(); }
		size_t max_size() const { return m_tree.max_size(); }

		// operator[]
		mapped_type &operator[](const key_type &key) {
			return (*((this->insert(ft::make_pair(key,mapped_type()))).first)).second; // ???
		}

		pair<iterator, bool> insert(const value_type &val) { return m_tree.insert(val); }
		iterator insert(iterator position, const value_type &val) {
			return m_tree(insert(position, val).first);
		}
		template <typename InputIterator>
		void insert(const InputIterator &first, const InputIterator &last) {
			for (InputIterator it = first; it != last; it++) {
				m_tree.insert(*it);
			}
		}

		void erase(iterator position) { m_tree.erase(position); }
		size_t erase(const key_type &key) { return m_tree.erase(ft::make_pair(key, mapped_type())); }
		void erase(iterator first, iterator last) { m_tree(m_tree.erase(first, last)); }
	};
}

#endif