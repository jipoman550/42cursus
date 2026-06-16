#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

int main()
{
	// 1. 과제 PDF에 제시된 기본 예제 테스트
	std::cout << "========== [ Subject Basic Test ] ==========" << std::endl;
	try
	{
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl; // 2 출력 기대
		std::cout << "Longest span:  " << sp.longestSpan() << std::endl;  // 14 출력 기대
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	// 2. 10,000개 이상의 숫자를 범위 기반 삽입으로 일괄 추가하는 대규모 테스트
	std::cout << "\n========== [ 10,000 Numbers Test (Range Insert) ] ==========" << std::endl;
	try
	{
		Span largeSp(10000);
		std::vector<int> randomNumbers;

		// 시드 초기화 및 난수 생성
		std::srand(static_cast<unsigned int>(std::time(NULL)));
		for (int i = 0; i < 10000; ++i)
		{
			randomNumbers.push_back(std::rand());
		}

		// 템플릿 함수를 이용한 범위 기반 데이터 삽입 (만 번의 함수 호출 대신 1번의 호출)
		largeSp.addNumbers(randomNumbers.begin(), randomNumbers.end());
		std::cout << "Successfully added 10,000 random numbers!" << std::endl;
		std::cout << "Shortest span: " << largeSp.shortestSpan() << std::endl;
		std::cout << "Longest span:  " << largeSp.longestSpan() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// 3. 예외 상황 처리 테스트 (데이터 부족, 용량 초과 방어 로직)
	std::cout << "\n========== [ Exception Handling Tests ] ==========" << std::endl;
	Span smallSp(2);

	try
	{
		std::cout << "Trying to get span from an empty Span..." << std::endl;
		smallSp.shortestSpan();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	try
	{
		smallSp.addNumber(42);
		std::cout << "\nTrying to get span from a Span with 1 element..." << std::endl;
		smallSp.longestSpan();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	try
	{
		smallSp.addNumber(21);
		std::cout << "\nTrying to add a number to a full Span..." << std::endl;
		// 현재 크기: 2/2, 여기서 데이터를 더 추가하면 예외가 발생해야 함.
		smallSp.addNumber(84);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	std::cout << "============================================================" << std::endl;

	return (0);
}
