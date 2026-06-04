#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

// 기본 생성자
Intern::Intern() {}

// 복사 생성자 (인턴은 고유의 속성(멤버 변수)이 없으므로 추가적인 동작이 필요 없습니다)
Intern::Intern(const Intern& other) {
	(void)other;
}

// 대입 연산자 (마찬가지로 복사할 속성이 없습니다)
Intern& Intern::operator=(const Intern& other) {
	(void)other;
	return *this;
}

// 소멸자
Intern::~Intern() {}

// --- 각 서류를 생성하여 반환하는 팩토리 헬퍼 함수들 ---
AForm* Intern::makeShrubbery(const std::string& target) const {
	return new ShrubberyCreationForm(target);
}

AForm* Intern::makeRobotomy(const std::string& target) const {
	return new RobotomyRequestForm(target);
}

AForm* Intern::makePresidential(const std::string& target) const {
	return new PresidentialPardonForm(target);
}

// --- makeForm 로직: if-else if 구조를 지양하고 멤버 함수 포인터를 활용 ---
AForm* Intern::makeForm(std::string formName, std::string target) {
	// 생성 가능한 서류 이름들을 매핑할 배열
	const std::string formNames[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	// 서류 생성을 담당하는 멤버 함수 포인터 배열 (formNames 배열과 인덱스가 일치하도록 설계)
	AForm* (Intern::*makeFuncs[3])(const std::string&) const = {
		&Intern::makeShrubbery,
		&Intern::makeRobotomy,
		&Intern::makePresidential
	};

	// 입력받은 서류 이름과 배열을 비교하여 일치하는 함수 포인터를 실행
	for (int i = 0; i < 3; i++) {
		if (formName == formNames[i]) {
			std::cout << "Intern creates " << formName << std::endl;
			// 해당 인덱스의 멤버 함수를 호출하여 new로 동적 할당된 AForm 포인터를 반환
			return (this->*makeFuncs[i])(target);
		}
	}

	// 존재하지 않는 엉뚱한 서류를 요구받았을 경우의 예외 처리
	std::cerr << "Error: Intern cannot create form '" << formName << "' (Unknown form type)" << std::endl;
	return NULL;
}