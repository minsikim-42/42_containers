#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <iostream>

#include "./vector.hpp"
#include "./utils.hpp"
#include "./map.hpp"
#include "./tree.hpp"

void map_test(void)
{
	std::cout << "\n================ Map Test =================\n\n";
	std::map<int, int> std_map;
	ft::map<int, int> map;
	std::cout << "std::begin : " << std_map.begin()->first << std::endl;
	std::cout << std::boolalpha << std_map.empty() << std::endl;

	std::cout << "begin : " << map.begin()->first << std::endl;
	std::cout << std::boolalpha << map.empty() << std::endl;

	map.insert(ft::pair<int, int>(10, 10));
	std_map.insert(std::pair<int, int>(10, 10));

	std::cout << "std::map[1] : " << std_map[10] << std::endl; 
	std::cout << "map[1] : " << map[10] << std::endl;
	// map[1] = 1;

	std::map<int, int> std_map2;
	ft::map<int, int> map2;

	std::cout << "\n================ Map::iterator Test =================\n\n";
	for (int i=20; i > 1; i--)
	{
		std_map[i] = i;
		map[i] = i;
	}
	std::cout << "size : " << map.size() << " " << std_map.size() << std::endl;
	std::cout << "max_size : " << map.max_size() << " " << std_map.max_size() << std::endl;
	// map.insert(ft::pair<int, int>(0, 5)); //////// 4th
	// map.insert(ft::pair<int, int>(2, 2));
	// map.insert(ft::pair<int, int>(3, 3));
	// map.insert(ft::pair<int, int>(4, 4));
	// map.insert(ft::pair<int, int>(5, 5));
	// std_map.insert(std::pair<int, int>(2, 2));
	// std_map.insert(std::pair<int, int>(3, 3));
	// std_map.insert(std::pair<int, int>(4, 4));
	// std_map.insert(std::pair<int, int>(5, 5));
	map.erase(5);
	std_map.erase(5);
	std::map<int, int>::iterator std_it = std_map.begin();
	ft::map<int, int>::iterator it = map.begin();
	try {
	for (int i = 1; i < 9; i++)
	{
		std::cout << "std::iterator : [" << (*std_it).first << "] " << (*std_it).second << std::endl; 
		std::cout << "iterator : [" << (*it).first << "] " << (*it).second << std::endl;
		std_it++;
		it++;
	}
	} catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	map[5] = 42;
	std_map[5] = 42;
	std::cout << "std_map[5] " << std_map[5] << std::endl; 
	std::cout << "map[5] " << map[5] << std::endl;
	// ft::map<int, int> temp(map);
	// temp[0] = 5;
	// map.swap(temp);
	// it = map.begin();
	// std::cout << "swap iterator : [" << (*it).first << "] " << (*it).second << std::endl;
}

void util_test(void)
{
	std::cout << "\n================ Utils Test =================\n\n";
	{
		std::cout << "\n================ pair Test =================\n";
		ft::pair<int, std::string> pair;
		ft::pair<int, std::string> pair2;
		std::pair<int, std::string> std_pair;
		std::pair<int, std::string> std_pair2;
		pair.first = 1;
		pair.second = "hihibig";
		pair2.first = 1;
		pair2.second = "hihi";

		std_pair.first = 1;
		std_pair.second = "hihibig";
		std_pair2.first = 1;
		std_pair2.second = "hihi";
		std::cout << "first: " << pair.first << ", second: " << pair.second << std::endl;
		std::cout << "std::operator< : " << std::boolalpha << (std_pair < std_pair2) << std::endl;
		std::cout << "operator< : " << std::boolalpha << (pair < pair2) << std::endl;
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
		std::vector<std::string>::reverse_iterator rit;
		ft::vector<std::string>::reverse_iterator rit2;
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
		rit = vec.rbegin();
		rit2 = vec2.rbegin();

		std::cout << it[2] << std::endl;
		std::cout << it2[2] << std::endl;
		ft::vector<std::string>::iterator iitt = it2;
		std::cout << "cap: " << vec.capacity() << ", size: " << vec.size() << std::endl;
		std::cout << "cap: " << vec2.capacity() << ", size: " << vec2.size() << std::endl;
		std::cout << std::boolalpha << vec.empty() << std::endl;
		std::cout << std::boolalpha << vec2.empty() << std::endl;
		std::cout << "std::front: " << vec.front() << std::endl;
		std::cout << "ft::front: " << vec2.front() << std::endl;
		std::cout << "std::it + 1: " << *(it + 1) << std::endl;
		std::cout << "ft::it + 1: " << *(iitt + 1) << std::endl;
		std::cout << "std::at [2]: " << (vec.at(2)) << std::endl;
		std::cout << "ft::at [2]: " << (vec2.at(2)) << std::endl;
		// rit = 1 + rit;
		// rit2 = 1 + rit2;
	}
}

void vector_test2()
{
	std::vector<int> myvector (3,100);
	std::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );

	for (; it != myvector.end(); it++)
		std::cout << *it << std::endl;

	// myvector.insert (it,2,300);

	// "it" no longer valid, get a new one:
	// it = myvector.begin();

	// std::vector<int> anothervector (2,400);
	// myvector.insert (it+2,anothervector.begin(),anothervector.end());

	// int myarray [] = { 501,502,503 };
	// myvector.insert (myvector.begin(), myarray, myarray+3);

	// std::cout << "myvector contains:";
	// for (it=myvector.begin(); it<myvector.end(); it++)
	// 	std::cout << ' ' << *it;
	// std::cout << '\n';
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

	// vector_test();

	// util_test();

	// map_test();

	vector_test2();
}