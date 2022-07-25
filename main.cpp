#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <iostream>

#include "./Vector.hpp"

void vector_test(void)
{
	{
		std::cout << "\n============ ft::Vector Test =============\n";
		ft::vector<int> vec(2);
		std::cout << vec.capacity() << std::endl;
		std::cout << std::boolalpha << vec.empty();
	}

	{
		std::cout << "\n============ std::Vector Test =============\n";
		std::vector<std::string> vec;
		ft::vector<std::string> vec2;
		std::vector<std::string>::iterator it;
		ft::vector<std::string>::iterator it2;
		// std::iterator::vector<std::string> it3; // error
		
		vec.push_back("abc");
		vec2.push_back("123");
		it = vec.begin();
		it2 = vec2.begin();
		std::cout << vec.capacity() << std::endl;
		std::cout << std::boolalpha << std::endl;
		std::cout << *it << std::endl;
	}
}

class test // explicit test
{
public:
	int num;
	test(int n) : num(n){};
};
void printTest(test te)
{
	std::cout << te.num << std::endl;
}

class test2
{
public:
	int num;
	explicit test2(int n) : num(n){};
};
void printTest2(test2 te)
{
	std::cout << te.num << std::endl;
}

int ret(void)
{
	return 42;
}
void testt(int i = ret())
{
	std::cout << "=: " << i << std::endl;
}

int main()
{
	std::vector<int>::reverse_iterator it;
	std::vector<std::string> vec_string;
	std::string te;
	std::cout << te << ": " << te.end() - te.begin() << ", " << te.capacity() << std::endl;
	te += '1';
	std::cout << te.size() << ": " << te.end() - te.begin() << ", " << te.capacity() << std::endl;
	te += "23456789012345678901234567890";
	std::cout << te.size() << ": " << te.end() - te.begin() << ", " << te.capacity() << std::endl;
	te += "12345678901234567890";
	std::cout << te.size() << ": " << te.end() - te.begin() << ", " << te.capacity() << std::endl;
	te += "2345678901234567890123456789012345678901234567890";
	std::cout << te.size() << ": " << te.end() - te.begin() << ", " << te.capacity() << std::endl;

	// ft::vector<std::string> ft_vec_string;

	testt();
	// ft_vec_string.push_back("string");
	// ft_vec_string.push_back("ft_string");

	// test
	// int n = 42;
	// printTest(n);
	// printTest2(n); // explicit ㄱㅐ쩐당...

	vector_test();
}