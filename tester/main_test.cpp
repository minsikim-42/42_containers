#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <iostream>

#include "../includes/vector.hpp"
#include "../includes/utils.hpp"
#include "../includes/map.hpp"
#include "../includes/tree.hpp"
#include "../includes/stack.hpp"

void printSize(ft::vector<int> vct)
{
	{
		ft::vector<int>::const_iterator it = vct.begin();
		ft::vector<int>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
}

void std_printSize(std::vector<int> vct)
{
	{
		std::vector<int>::const_iterator it = vct.begin();
		std::vector<int>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
}

void tester_stack() {
	std::stack<int>::container_type std_con_type;
	ft::stack<int>::container_type con_type;

	std_con_type.push_back(21);
	std_con_type.push_back(42);
	std_con_type.push_back(1337);
	std_con_type.push_back(19);
	std_con_type.push_back(0);
	std_con_type.push_back(183792);

	con_type.push_back(21);
	con_type.push_back(42);
	con_type.push_back(1337);
	con_type.push_back(19);
	con_type.push_back(0);
	con_type.push_back(183792);
	
	std::stack<int> std_st(std_con_type);
	ft::stack<int> st(con_type);

	std::cout << "empty: " << st.empty() << std::endl;
	std::cout << "size: " << st.size() << std::endl;

	std_st.push(1);
	st.push(1);
	std_st.push(2);
	st.push(2);
	std_st.push(3);
	st.push(3);
	std_st.push(4);
	st.push(4);
	std_st.push(5);
	st.push(5);
	std_st.push(6);
	st.push(6);

	std::cout << "empty: " << std_st.empty() << st.empty() << std::endl;
	std::cout << "size: " << std_st.size() << st.size() << std::endl;
	std::cout << std_st.size() << "	vs size (ft) " << st.size() << std::endl;

	{
		std::cout << std::endl << "Content was:" << std::endl;
		while (st.size() != 0) {
			std::cout << "-" << std_st.top() << "	vs (ft) " << st.top() << std::endl;
			st.pop(); std_st.pop();
		}
	}
}

void tester_relation_ope() {
	ft::map<char, int> mp1;
	ft::map<char, int> mp2;

	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

	std::cout << "eq: " << (mp1 == mp1) << " | ne: " << (mp1 != mp1) << std::endl;
	std::cout << "eq: " << (mp1 == mp2) << " | ne: " << (mp1 != mp2) << std::endl;
}

void tester_copycon() {
	std::cout << "=================ft=====================\n";
	ft::vector<int> vct(5);
	ft::vector<int>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	ft::vector<int> vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;

	it = vct.begin();
	ft::vector<int> vct_copy(vct);
	for (int i = 0; it != ite; ++it)
		*it = ++i * 7;
	printSize(vct);
	std::cout << "---------vct_copy---------\n";
	printSize(vct_copy);
}

void std_tester_copycon() {
	std::cout << "=================std=================\n";
	std::vector<int> vct(5);
	std::vector<int>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	std::vector<int> vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;

	it = vct.begin();
	std::vector<int> vct_copy(vct);
	for (int i = 0; it != ite; ++it)
		*it = ++i * 7;
	std_printSize(vct);
	std::cout << "---------vct_copy---------\n";
	std_printSize(vct_copy);
}

void tester_insert() {
	std::cout << "===================ft=====================\n";
	ft::vector<int> vct(10);
	ft::vector<int> vct2;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	printSize(vct);

	vct2.insert(vct2.end(), 42); ////////////// error
	vct2.insert(vct2.begin(), 2, 21);
	printSize(vct2);
}

void std_tester_insert() {
	std::cout << "====================std======================\n";
	std::vector<int> vct(10);
	std::vector<int> vct2;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	std_printSize(vct);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	std_printSize(vct2);
}

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
	// map.insert(ft::pair<int, int>(2, 2));
	// std_map.insert(std::pair<int, int>(2, 2));
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

void vector_test2() // cplusplus
{
	std::vector<int> std_vec(3,100);
	ft::vector<int> ft_vec(3, 100);
	std::vector<int>::iterator std_it;
	ft::vector<int>::iterator ft_it;

	std_it = std_vec.begin();
	std_it = std_vec.insert ( std_it , 200 );
	ft_it = ft_vec.begin();
	ft_it = ft_vec.insert(ft_it, 200);

	for (; std_it != std_vec.end(); std_it++)
		std::cout << *std_it << std::endl;
	for (; ft_it != ft_vec.end(); ft_it++)
		std::cout << *ft_it << std::endl;

	std_vec.insert (std_it,2,300);
	ft_vec.insert(ft_it, 2, 300);

	std_it += 2;
	ft_it += 2;
	std::cout << *std_it << "vs (ft)" << *ft_it << std::endl;
	// "std_it" no longer valid, get a new one:
	std_it = std_vec.begin();
	ft_it = ft_vec.begin();

	std::cout << "size : " << std_vec.size() << " vs (ft)" << ft_vec.size() << std::endl;

	// std::vector<int> anothervector (2,400);
	// std_vec.insert (std_it+2,anothervector.begin(),anothervector.end());

	// int myarray [] = { 501,502,503 };
	// std_vec.insert (std_vec.begin(), myarray, myarray+3);

	// std::cout << "std_vec contains:";
	// for (std_it=std_vec.begin(); std_it<std_vec.end(); std_it++)
	// 	std::cout << ' ' << *std_it;
	// std::cout << '\n';
}

void tester_size() {
	std::cout << "=====================ft====================\n";
	const int start_size = 7;
	ft::vector<int> vct(start_size, 20);
	ft::vector<int> vct2;
	ft::vector<int>::iterator it = vct.begin();

	for (int i = 2; i < start_size; ++i)
		it[i] = (start_size - i) * 3;

	{ // print
		ft::vector<int>::const_iterator it = vct.begin();
		ft::vector<int>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	vct.resize(10, 42);
	{ // print
		ft::vector<int>::const_iterator it = vct.begin();
		ft::vector<int>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
}

void std_tester_size() {
	std::cout << "==================std=====================\n";
	const int start_size = 7;
	std::vector<int> vct(start_size, 20);
	std::vector<int> vct2;
	std::vector<int>::iterator it = vct.begin();

	for (int i = 2; i < start_size; ++i)
		it[i] = (start_size - i) * 3;

	{ // print
		std::vector<int>::const_iterator it = vct.begin();
		std::vector<int>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	vct.resize(10, 42);
	{ // print
		std::vector<int>::const_iterator it = vct.begin();
		std::vector<int>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
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

	// vector_test();

	// util_test();

	// map_test();

	// vector_test2();

	// std_tester_size();
	// tester_size();

	// std_tester_insert();
	// tester_insert();

	// std_tester_copycon();
	// tester_copycon();

	// tester_relation_ope();

	// ft::map<int, int> const mp;
	// ft::map<int, int>::iterator it = mp.begin(); // <-- error expected

	// std::map<int, int> const std_mp;
	// std::map<int, int>::iterator std_it = std_mp.begin();
	// (void)it;
	// (void)std_it;

	tester_stack();
}