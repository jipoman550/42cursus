#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv) {
	// 프로그램은 반드시 1개의 인자(문자열 리터럴)만 받아야 합니다.
	if (argc != 2)
	{
		std::cerr << "Usage: ./convert <literal>" << std::endl;
		return (1);
	}
	// 인스턴스를 생성하지 않고, static 메서드를 통해 즉시 변환 호출
	ScalarConverter::convert(argv[1]);

	return (0);
}