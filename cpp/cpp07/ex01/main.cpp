#include <iostream>
#include <string>
#include "iter.hpp"

// 1) 값을 단순히 출력하는 테스트용 함수 (const 참조)
template <typename T>
void printElement(const T& element)
{
	std::cout << element << " ";
}

// 2) 값을 1씩 증가시키는 테스트용 함수 (일반 참조)
template <typename T>
void incrementElement(T& element)
{
	element += 1;
}

int main(void)
{
	// 1 & 2: 일반 int 배열 테스트
	int intArray[] = {1, 2, 3, 4, 5};
	std::size_t intLen = sizeof(intArray) / sizeof(intArray[0]);

	std::cout << "[Original intArray]: ";
	::iter(intArray, intLen, printElement<int>);
	std::cout << std::endl;

	::iter(intArray, intLen, incrementElement<int>);
	std::cout << "[Incremented intArray]: ";
	::iter(intArray, intLen, printElement<int>);
	std::cout << std::endl;

	// 3: std::string 배열 테스트
	std::string strArray[] = {"Hello", "42", "Gyeongsan", "C++98"};
	std::size_t strLen = sizeof(strArray) / sizeof(strArray[0]);

	std::cout << "[strArray]: ";
	::iter(strArray, strLen, printElement<std::string>);
	std::cout << std::endl;

	// 4: const int 배열 (읽기 전용) 테스트 - const 안전성 검증
	const int constIntArray[] = {10, 20, 30, 40, 50};
	std::size_t constIntLen = sizeof(constIntArray) / sizeof(constIntArray[0]);

	std::cout << "[constIntArray]: ";
	// const 배열이므로 값을 변경하는 함수는 전달할 수 없지만, 출력(const 참조) 함수는 완벽히 작동합니다.
	::iter(constIntArray, constIntLen, printElement<int>);
	std::cout << std::endl;

	return 0;
}