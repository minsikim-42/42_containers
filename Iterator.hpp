#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include <iterator>

namespace ft
{
	struct input_iterator_tag {}; // what is it??

	template <typename Category,
			typename T,
			typename Distance = std::ptrdiff_t,
			typename Pointer = T*,
			typename Reference = T&> // what the hell is it?
	struct iterator
	{
		typedef T		value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

} // namespace ft


#endif