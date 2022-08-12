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

		first_type first;
		second_type second;

		pair() : first(), second() {};
		pair(const first_type &t1, const second_type &t2) : first(t1), second(t2) {};

		template <typename U1, typename U2>
		pair(const pair<U1, U2> &origin) : first(origin.first), second(origin.second) {};

		// operator =
		pair &operator=(const pair &origin)
		{
			first = origin.first;
			second = origin.second;
			return *this;
		}
	};
	template<typename T1, typename T2>
	bool operator==(const pair<T1, T2> &p1, const pair<T1, T2> &p2) {
		// std::cout << "\nfirst : " << p1.first << " vs " << p2.first << std::endl;
		// std::cout << "second : " << p1.second << " vs " << p2.second << std::endl;
		// std::cout << std::boolalpha << (p1.first == p2.first) << " vs " << (p1.first == p2.second) << "\n\n";
		return (p1.first == p2.first && p1.second == p2.second);
	}
	template<typename T1, typename T2>
	bool operator!=(const pair<T1, T2> &p1, const pair<T1, T2> &p2) {
		return !(p1 == p2);
	}
	template<typename T1, typename T2>
	bool operator<(const pair<T1, T2> &p1, const pair<T1, T2> &p2) {
		return (p1.first < p2.first || p1.second < p2.second);
	}
	template<typename T1, typename T2>
	bool operator<=(const pair<T1, T2> &p1, const pair<T1, T2> &p2) {
		return (p1.first <= p2.first || p1.second <= p2.second);
	}
	template<typename T1, typename T2>
	bool operator>(const pair<T1, T2> &p1, const pair<T1, T2> &p2) {
		return (p1.first > p2.first || p1.second > p2.second);
	}
	template<typename T1, typename T2>
	bool operator>=(const pair<T1, T2> &p1, const pair<T1, T2> &p2) {
		return (p1.first >= p2.first || p1.second >= p2.second);
	}

	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 first, T2 second) {
		return pair<T1, T2>(first, second);
	}

	// equal
	template <typename IT1, typename IT2>
	bool equal(IT1 first1, IT1 last1, IT2 first2)
	{
		while (first1 != last1)
		{
			// std::cout << first1->first << " vs " << first2->first << std::endl;
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
	template <class InputIterator1, class InputIterator2, typename Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1)) // 2보다 크면 false
				return false;
			else if (comp(*first1, *first2)) // 작으면 true
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2); // 다르면 true 
	}
} // namespace ft


#endif