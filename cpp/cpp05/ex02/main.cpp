#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <ctime>

int main() {
	// Robotomy의 50% 확률을 위해 랜덤 시드 초기화
	std::srand(std::time(NULL));

	std::cout << "=================================================" << std::endl;
	std::cout << "        C++ Module 05 ex02: Abstract Form        " << std::endl;
	std::cout << "=================================================" << std::endl << std::endl;

	// 관료 객체 3명 생성 (가장 높은 권한, 중간 권한, 가장 낮은 권한)
	Bureaucrat highRank("Boss", 1);
	Bureaucrat midRank("Manager", 50);
	Bureaucrat lowRank("Intern", 150);

	// 폼 객체 3종류 생성
	ShrubberyCreationForm shrubbery("Home");		// Sign: 145, Exec: 137
	RobotomyRequestForm robotomy("Bender");			// Sign:  72, Exec:  45
	PresidentialPardonForm pardon("Arthur Dent");	// Sign:  25, Exec:   5

	std::cout << "\n[Test 1] Execution Without Sign Test" << std::endl;
	// 서명되지 않은 상태에서 실행 시도 -> 예외 발생 (NotSignedException)
	highRank.executeForm(shrubbery);

	std::cout << "\n[Test 2] Shrubbery Creation Form (Sign: 145, Exec: 137)" << std::endl;
	lowRank.signForm(shrubbery);    // 실패 (150 > 145)
	midRank.signForm(shrubbery);    // 성공 (50 <= 145)
	lowRank.executeForm(shrubbery); // 실패 (150 > 137)
	midRank.executeForm(shrubbery); // 성공 -> Home_shrubbery 파일 생성

	std::cout << "\n[Test 3] Robotomy Request Form (Sign: 72, Exec: 45)" << std::endl;
	midRank.signForm(robotomy);     // 성공 (50 <= 72)
	midRank.executeForm(robotomy);  // 실패 (50 > 45) -> 권한 부족
	highRank.executeForm(robotomy); // 성공 -> 50% 확률 결과 출력
	highRank.executeForm(robotomy); // 다시 실행 (확률 체크용)

	std::cout << "\n[Test 4] Presidential Pardon Form (Sign: 25, Exec: 5)" << std::endl;
	midRank.signForm(pardon);       // 실패 (50 > 25)
	highRank.signForm(pardon);      // 성공 (1 <= 25)
	midRank.executeForm(pardon);    // 실패 (50 > 5)
	highRank.executeForm(pardon);   // 성공 -> Zaphod Beeblebrox 출력

	std::cout << "\n[Test 5] Polymorphism Test (Pointer Array)" << std::endl;
	// AForm을 포인터 배열로 묶어 다형성 실행을 검증
	AForm* forms[] = { &shrubbery, &robotomy, &pardon };
	for (int i = 0; i < 3; i++)
	{
		std::cout << "\n--- Checking form: " << forms[i]->getName() << " ---" << std::endl;
		// 모든 서류가 서명된 상태이므로, highRank는 권한(1)이 모두 최고라 전부 실행 가능
		highRank.executeForm(*forms[i]);
	}

	std::cout << "\n=================================================" << std::endl;
	std::cout << "                 All Tests Done                  " << std::endl;
	std::cout << "=================================================" << std::endl;

	return 0;
}