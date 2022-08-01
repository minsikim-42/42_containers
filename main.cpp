#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <iostream>

#include "./vector.hpp"
#include "./Utils.hpp"

void pair_test(void)
{
	std::cout << "\n================ Utils Test =================\n\n";
	{
		std::cout << "\n================ pair Test =================\n";
		ft::pair<int, std::string> pair;
		std::pair<int, std::string> std_pair;
		pair.m_first = 1;
		pair.m_second = "hihi";
		std::cout << "first: " << pair.m_first << ", second: " << pair.m_second << std::endl;
	}
	{
		std::cout << "\n================ equal Test =================\n";
		std::string str1 = "hihi1";
		std::string str2 = "hihi123";
		std::cout << "ft: " << std::boolalpha << ft::equal(str1.begin(), str1.end(), str2.begin()) << std::endl;
		std::cout << "std: " << std::boolalpha << std::equal(str1.begin(), str1.end(), str2.begin()) << std::endl;
	}
	{
		std::cout << "\n============ lexicographical_compare Test =============\n";
		std::string str1 = "hihi15";
		std::string str2 = "hihi123";

		std::cout << "std: " << std::boolalpha << std::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end()) << std::endl;
		std::cout << "ft: " << std::boolalpha << ft::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end()) << std::endl;
	}
}

void vector_test(void)
{
	std::cout << "\n============ ft::Vector Test =============\n";
	{
		std::vector<std::string> vec;
		ft::vector<std::string> vec2;
		std::vector<std::string>::iterator it;
		ft::vector<std::string>::iterator it2;
		// std::iterator::vector<std::string> it3; // error
		
		// vec.reserve(1);
		// vec2.reserve(1);
		vec.push_back("a");
		vec.push_back("b");
		vec.push_back("c");
		vec2.push_back("a");
		vec2.push_back("b");
		vec2.push_back("c");
		it = vec.begin();
		it2 = vec2.begin();
		std::cout << it[2] << std::endl;
		std::cout << it2[2] << std::endl;
		ft::vector<std::string>::iterator iitt = it2;
		std::cout << "cap: " << vec.capacity() << ", size: " << vec.size() << std::endl;
		std::cout << "cap: " << vec2.capacity() << ", size: " << vec2.size() << std::endl;
		std::cout << std::boolalpha << vec.empty() << std::endl;
		std::cout << std::boolalpha << vec2.empty() << std::endl;
		std::cout << "std::front: " << vec.front() << std::endl;
		std::cout << "ft::front: " << vec2.front() << std::endl;
		std::cout << "std::++it: " << *(++it) << std::endl;
		std::cout << "ft::++it: " << *(++iitt) << std::endl;
		std::cout << "std::at [2]: " << (vec.at(2)) << std::endl;
		std::cout << "ft::at [2]: " << (vec2.at(2)) << std::endl;
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
	// std::vector<int>::reverse_iterator it;
	// std::vector<std::string> vec_string;
	// std::string te;
	// std::cout << te << ": " << te.end() - te.begin() << ", " << te.capacity() << std::endl;
	// te += '1';
	// std::cout << te.size() << ": " << te.end() - te.begin() << ", " << te.capacity() << std::endl;
	// te += "23456789012345678901234567890";
	// std::cout << te.size() << ": " << te.end() - te.begin() << ", " << te.capacity() << std::endl;
	// te += "12345678901234567890";
	// std::cout << te.size() << ": " << te.end() - te.begin() << ", " << te.capacity() << std::endl;
	// te += "2345678901234567890123456789012345678901234567890";
	// std::cout << te.size() << ": " << te.end() - te.begin() << ", " << te.capacity() << std::endl;

	// ft::vector<std::string> ft_vec_string;

	// testt();
	// ft_vec_string.push_back("string");
	// ft_vec_string.push_back("ft_string");

	// test
	// int n = 42;
	// printTest(n);
	// printTest2(n); // explicit ㄱㅐ쩐당...

	vector_test();

	pair_test();
}