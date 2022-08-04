#ifndef UTILS_HPP
# define UTILS_HPP
#include <iostream>

namespace ft
{
	// enable_if
	template <bool B, class T = void> // why void?
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };

	// is_
	template <typename T>
	struct is_integral {
		static const bool value = false;
	};
	template <>
	struct is_integral<int> {
		static const bool value = true;
	};
	// bool, char, char8_t, char16_t, char32_t, wchar_t, short, int, long, long long -> true
	template <>
	struct is_integral<bool> {
		static const bool value = true;
	};
	template <>
	struct is_integral<char> {
		static const bool value = true;
	};
	template <>
	struct is_integral<wchar_t> {
		static const bool value = true;
	};
	template <>
	struct is_integral<char16_t> {
		static const bool value = true;
	};
	template <>
	struct is_integral<char32_t> {
		static const bool value = true;
	};


	// pair
	template <typename T1, typename T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 m_first;
		T2 m_second;

		pair() : m_first(), m_second() {};
		pair(T1 const &t1, T2 const &t2) : m_first(t1), m_second(t2) {};

		template <typename U1, typename U2>
		pair(const pair<U1, U2> &origin) : m_first(origin.m_first), m_second(origin.m_second) {};

		// operator =
		pair &operator=(const pair &origin)
		{
			m_first = origin.m_first;
			m_second = origin.m_second;
			return *this;
		}

	};
	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 first, T2 second) {
		return pair<T1, T2>(first, second);
	}

	// equal
	template <typename IT1, typename IT2>
	bool equal(IT1 first1, IT1 last, IT2 first2)
	{
		while (first1 != last)
		{
			// std::cout << *first1 << " vs " << *first2 << std::endl;
			if (*first1 != *first2)
				return false;
			first1++;
			first2++;
		}
		return true;
	}

	// 사전식 비교
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) // 2보다 크면 false
				return false;
			else if (*first1 < *first2) // 작으면 true
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2); // 다르면 true 
	}
} // namespace ft


#endif