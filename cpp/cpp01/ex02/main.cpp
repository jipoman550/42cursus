#include <iostream>
#include <string>

int main() {
	// "HI THIS IS BRAIN"으로 초기화된 문자열 변수 선언
	std::string str = "HI THIS IS BRAIN";

	// 문자열 변수를 가리키는 포인터 선언
	// 포인터는 주소값을 저장하는 독립적인 변수입니다.
	std::string* stringPTR = &str;

	// 문자열 변수에 대한 참조자(별명) 선언
	// 참조자는 원본 변수와 완전히 동일한 메모리 공간을 가리키는 또 다른 이름입니다.
	std::string& stringREF = str;

	// --- 주소 출력 ---
	std::cout << "--- PRINT ADDRESSES ---" << std::endl;
	// 1. 문자열 변수(str)의 메모리 주소
	std::cout << "Address of the string variable: " << &str << std::endl;
	// 2. stringPTR이 들고 있는 주소 (str의 주소를 가리킴)
	std::cout << "Address held by stringPTR:      " << stringPTR << std::endl;
	/*// [test!] stringPTR 자체의 주소
	std::cout << "Address held by &stringPTR:      " << &stringPTR << std::endl;*/
	// 3. stringREF가 참조하는 변수의 주소 (str의 주소와 동일)
	std::cout << "Address held by stringREF:      " << &stringREF << std::endl;
	std::cout << std::endl;

	// --- 값 출력 ---
	std::cout << "--- PRINT VALUES ---" << std::endl;
	// 1. 문자열 변수의 값
	std::cout << "Value of the string variable:  " << str << std::endl;
	// 2. stringPTR이 가리키는 곳의 값 (역참조 연산자 '*' 사용)
	std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
	// 3. stringREF가 참조하는 값 (일반 변수처럼 사용)
	std::cout << "Value pointed to by stringREF: " << stringREF << std::endl;

	return 0;
}
