#include <iostream>
#include <string>
#include "Array.hpp"

int main(void)
{
	std::cout << "=== 1. int Array 생성 및 초기화 테스트 ===" << std::endl;
	Array<int> intArray(5);
	for (unsigned int i = 0; i < intArray.size(); ++i)
	{
		intArray[i] = i * 10;
	}

	std::cout << "intArray: ";
	for (unsigned int i = 0; i < intArray.size(); ++i)
	{
		std::cout << intArray[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "\n=== 2. 깊은 복사 (Deep Copy) 테스트 ===" << std::endl;
	Array<int> copyArray(intArray); // 복사 생성자
	Array<int> assignArray;
	assignArray = intArray;         // 복사 대입 연산자

	std::cout << "원본 및 복사본 초기 상태:" << std::endl;
	std::cout << "intArray[0]: " << intArray[0] << ", copyArray[0]: " << copyArray[0] << std::endl;

	// 복사본 수정
	copyArray[0] = 999;
	assignArray[1] = 888;

	std::cout << "\n복사본 수정 후 상태 (원본은 변하지 않아야 함):" << std::endl;
	std::cout << "intArray[0]: " << intArray[0] << ", [1]: " << intArray[1] << " (Original)" << std::endl;
	std::cout << "copyArray[0]: " << copyArray[0] << " (Copy Constructor)" << std::endl;
	std::cout << "assignArray[1]: " << assignArray[1] << " (Assignment Operator)" << std::endl;

	std::cout << "\n=== 3. 예외 처리 (Out of Bounds) 테스트 ===" << std::endl;
	try
	{
		std::cout << "intArray[5] 접근 시도... (크기가 5이므로 범위를 벗어남)" << std::endl;
		intArray[5] = 42;
	}
	catch (const std::exception& e)
	{
		std::cerr << "예외 발생: " << e.what() << std::endl;
	}

	try
	{
		std::cout << "intArray[-1] 접근 시도... (-1은 unsigned int 캐스팅으로 인해 최댓값이 되어 예외가 발생함)" << std::endl;
		intArray[-1] = 42;
	}
	catch (const std::exception& e)
	{
		std::cerr << "예외 발생: " << e.what() << std::endl;
	}

	std::cout << "\n=== 4. 다른 타입 (std::string) 지원 테스트 ===" << std::endl;
	Array<std::string> strArray(3);
	strArray[0] = "Hello";
	strArray[1] = "42";
	strArray[2] = "School";

	for (unsigned int i = 0; i < strArray.size(); ++i)
	{
		std::cout << "strArray[" << i << "]: " << strArray[i] << std::endl;
	}

	std::cout << "\n=== 5. 빈 배열 (Empty Array) 테스트 ===" << std::endl;
	Array<double> emptyArray;
	std::cout << "emptyArray.size(): " << emptyArray.size() << std::endl;

	std::cout << "\n모든 테스트가 정상적으로 완료되었습니다." << std::endl;

	return (0);
}