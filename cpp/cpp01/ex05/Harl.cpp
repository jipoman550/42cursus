#include "Harl.hpp"

// Harl 클래스의 생성자입니다.
// 객체 생성 시 특별한 초기화 작업이 없으므로 비워둡니다.
Harl::Harl() {}

// Harl 클래스의 소멸자입니다.
// 객체 소멸 시 특별한 정리 작업이 없으므로 비워둡니다.
Harl::~Harl() {}

// DEBUG 수준의 메시지를 표준 출력으로 보냅니다.
void Harl::debug(void)
{
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger." << std::endl;
	std::cout << "I really do!" << std::endl << std::endl;
}

// INFO 수준의 메시지를 표준 출력으로 보냅니다.
void Harl::info(void)
{
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money." << std::endl;
	std::cout << "You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl << std::endl;
}

// WARNING 수준의 메시지를 표준 출력으로 보냅니다.
void Harl::warning(void)
{
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free." << std::endl;
	std::cout << "I’ve been coming for years whereas you started working here since last month." << std::endl << std::endl;
}

// ERROR 수준의 메시지를 표준 출력으로 보냅니다.
void Harl::error(void)
{
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl << std::endl;
}

// 주어진 'level' 문자열과 일치하는 불평 함수를 호출합니다.
void Harl::complain(std::string level)
{
	// 1. 멤버 함수 포인터 배열을 선언합니다.
	// 각 원소는 Harl 클래스의 private 멤버 함수(debug, info, warning, error)를 가리킵니다.
	// 이 방식은 if-else 체인을 대체하여 코드의 유연성과 확장성을 높입니다.
	void (Harl::*funcs[])(void) =
	{
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};

	// 2. 각 함수에 해당하는 레벨을 문자열 배열로 선언합니다.
	// funcs 배열의 인덱스와 동일한 순서로 레벨을 매칭합니다.
	std::string levels[] =
	{
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};

	// 3. 루프를 돌면서 입력된 'level'과 일치하는 레벨을 찾습니다.
	for (int i = 0; i < 4; i++)
	{
		// 입력된 level이 levels 배열의 현재 요소와 일치하는지 확인합니다.
		if (levels[i] == level)
		{
			// 일치하는 경우, funcs 배열에서 해당 인덱스의 멤버 함수 포인터를 호출합니다.
			// (this->*funcs[i])() 문법은 멤버 함수 포인터를 통해 현재 객체(this)의 멤버 함수를 호출하는 C++의 표준 방식입니다.
			(this->*funcs[i])();
			// 함수를 실행했으므로 더 이상 루프를 진행할 필요가 없어 반환합니다.
			return ;
		}
	}
	// 루프가 끝날 때까지 일치하는 레벨을 찾지 못한 경우,
	// 알 수 없는 레벨임을 알리는 메시지를 출력합니다.
	std::cout << "[ Probably complaining about insignificant problems ]" << std::endl << std::endl;
}
