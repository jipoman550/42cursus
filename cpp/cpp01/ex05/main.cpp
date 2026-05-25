#include "Harl.hpp"

// 프로그램의 주 진입점입니다.
int main(void)
{
	// Harl 클래스의 인스턴스를 생성합니다.
	Harl harl;

	// 정의된 각 레벨에 대해 complain 함수를 호출하여 테스트합니다.
	std::cout << "--- Testing DEBUG ---" << std::endl;
	harl.complain("DEBUG");

	std::cout << "--- Testing INFO ---" << std::endl;
	harl.complain("INFO");

	std::cout << "--- Testing WARNING ---" << std::endl;
	harl.complain("WARNING");

	std::cout << "--- Testing ERROR ---" << std::endl;
	harl.complain("ERROR");

	// 정의되지 않은 레벨에 대한 처리를 테스트합니다.
	std::cout << "--- Testing INVALID ---" << std::endl;
	harl.complain("INVALID_LEVEL");

	return 0;
}
