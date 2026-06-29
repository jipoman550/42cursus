#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main() {
	// 1. std::vector 테스트
	std::cout << "========== [ std::vector Test ] ==========" << std::endl;
	std::vector<int> vec;

	// C++98 표준을 준수하기 위해 반복문으로 push_back 사용
	for (int i = 0; i < 5; ++i)
	{
		vec.push_back(i * 10); // 0, 10, 20, 30, 40 추가
	}

	try
	{
		std::cout << "Looking for 20..." << std::endl;
		std::vector<int>::iterator it1 = easyfind(vec, 20);
		std::cout << "Success! Found value: " << *it1 << std::endl;

		std::cout << "\nLooking for 42..." << std::endl;
		std::vector<int>::iterator it2 = easyfind(vec, 42); // 존재하지 않는 값
		std::cout << "Success! Found value: " << *it2 << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	// 2. std::list 테스트
	std::cout << "\n========== [ std::list Test ] ==========" << std::endl;
	std::list<int> lst;

	for (int i = 0; i < 5; ++i)
	{
		lst.push_back(i * 5); // 0, 5, 10, 15, 20 추가
	}

	try
	{
		std::cout << "Looking for 15..." << std::endl;
		std::list<int>::iterator it3 = easyfind(lst, 15);
		std::cout << "Success! Found value: " << *it3 << std::endl;

		std::cout << "\nLooking for 99..." << std::endl;
		std::list<int>::iterator it4 = easyfind(lst, 99); // 존재하지 않는 값
		std::cout << "Success! Found value: " << *it4 << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << "==========================================" << std::endl;

	return (0);
}