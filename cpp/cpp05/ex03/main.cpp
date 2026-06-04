#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"
#include <ctime>

int main() {
	// Robotomy의 50% 확률을 위해 랜덤 시드 초기화
	std::srand(std::time(NULL));

	std::cout << "=================================================" << std::endl;
	std::cout << "          C++ Module 05 ex03: Intern             " << std::endl;
	std::cout << "=================================================" << std::endl << std::endl;

	Intern someRandomIntern;
	Bureaucrat boss("Boss", 1); // 폼들을 모두 승인/실행할 수 있는 최고 권한 관료

	std::cout << "[Test 1] Intern creating valid forms" << std::endl;
	// 인턴이 3가지 종류의 유효한 폼을 정상적으로 생성하는지 확인 (팩토리 패턴 동작 검증)
	AForm* form1 = someRandomIntern.makeForm("shrubbery creation", "Garden");
	AForm* form2 = someRandomIntern.makeForm("robotomy request", "Bender");
	AForm* form3 = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");

	std::cout << "\n[Test 2] Intern creating an unknown form" << std::endl;
	// 존재하지 않는 엉뚱한 폼 이름을 전달했을 때의 예외 처리 및 NULL 반환 확인
	AForm* formUnknown = someRandomIntern.makeForm("time travel request", "Marty");

	std::cout << "\n[Test 3] Bureaucrat signing and executing the forms" << std::endl;
	// 인턴이 생성한 서류들(다형성 AForm*)을 Boss가 서명하고 실행하는 워크플로우 검증
	if (form1) {
		boss.signForm(*form1);
		boss.executeForm(*form1);
	}
	std::cout << "---------------------------------" << std::endl;
	if (form2) {
		boss.signForm(*form2);
		boss.executeForm(*form2);
	}
	std::cout << "---------------------------------" << std::endl;
	if (form3) {
		boss.signForm(*form3);
		boss.executeForm(*form3);
	}

	std::cout << "\n[Test 4] Memory Clean-up" << std::endl;
	// 인턴이 'new'로 동적 할당한 객체들을 잊지 않고 메모리 해제하여 누수(Leak) 방지
	delete form1;
	delete form2;
	delete form3;
	// formUnknown은 NULL이므로 delete해도 C++ 문법상 안전하지만 명확하게 작성합니다.
	if (formUnknown) delete formUnknown;
	std::cout << "Forms successfully deleted. No memory leaks!" << std::endl;

	std::cout << "\n=================================================" << std::endl;
	std::cout << "                 All Tests Done                  " << std::endl;
	std::cout << "=================================================" << std::endl;

	return 0;
}