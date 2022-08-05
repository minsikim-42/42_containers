#include <iostream>


template <bool b, class pair_type>
struct enable_if {};

template <class pair_type>
struct enable_if<true, pair_type> { typedef pair_type type; };

template <class pair_type, typename std::enable_if<std::is_integral<pair_type>::value, pair_type>::type* = nullptr>
void do_stuff(pair_type& t) {
  std::cout << "do_stuff integral\n";
  // 정수 타입들을 받는 함수 (int, char, unsigned, etc.)
}

template <class pair_type,
          typename std::enable_if<std::is_class<pair_type>::value, pair_type>::type* = nullptr>
void do_stuff(pair_type& t) {
  // 일반적인 클래스들을 받음
}

int main() {
	std::string hi = "abc";
	std::string::iterator it = hi.begin();
	for (; it != hi.end(); it++)
		std::cout << *it << std::endl;
	it--;
	try {it += 100;}
	catch (int e) {
		std::cout << "error\n";
	}
	try {for (; it != hi.end(); it++)
		std::cout << *it << std::endl;}
	catch (int e) {
		std::cout << "error\n";
	}
	
	hi += "123";
	for (; it != hi.end(); it++)
		std::cout << *it << std::endl;
    return 0;
}