#ifndef INTERN_HPP
# define INTERN_HPP

# include <iostream>
# include <string>
# include "AForm.hpp"

class Intern {
private:
	// 내부 팩토리 동작을 수행할 private 헬퍼 함수들입니다.
	// 인턴 자체의 상태를 변경하지 않으므로 const 멤버 함수로 선언합니다.
	AForm* makeShrubbery(const std::string& target) const;
	AForm* makeRobotomy(const std::string& target) const;
	AForm* makePresidential(const std::string& target) const;

public:
	// Orthodox Canonical Form (OCCF) 준수
	// 인턴은 고유의 이름이나 등급 같은 속성이 전혀 없으므로 기본 구조만 갖춥니다.
	Intern();
	Intern(const Intern& other);
	Intern& operator=(const Intern& other);
	~Intern();

	// 핵심 멤버 함수 (Factory Method)
	// 주어진 문자열(formName)과 대상(target)에 맞는 서류 객체를 동적 할당(new)하여 반환합니다.
	// 일치하는 것이 없으면 명확한 에러를 출력하고 NULL을 반환합니다.
	AForm* makeForm(std::string formName, std::string target);
};

#endif