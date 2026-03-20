#include <iostream>
#include <string>
#include "PhoneBook.hpp"

int main()
{
	// 1. PhoneBook 인스턴스(객체) 생성
	PhoneBook	phoneBook;
	std::string	command;

	// 환영 메시지는 루프 시작 전에 한 번만!
	std::cout << "Welcome to My Awesome PhoneBook!" << std::endl;

	// 2. 무한 루프 시작
	while (true)
	{
		// 3. 프롬프트 출력 및 사용자 입력 받기
		std::cout << "Enter command (ADD, SEARCH, EXIT): ";

		// std::cin >> command 보다는 std::getline이 공백 처리에 더 안전합니다.
		if (!std::getline(std::cin, command))
		{
			// Ctrl+D (EOF) 입력 시 루프를 안전하게 빠져나갑니다.
			break;
		}

		// 4. 명령어 비교 및 수행
		if (command == "ADD")
		{
			phoneBook.addContact();
		}
		else if (command == "SEARCH")
		{
			phoneBook.searchContact();
		}
		else if (command == "EXIT")
		{
			std::cout << "The program quits and the contacts are lost forever!" << std::endl;
			break ; // 루프 탈출 후 프로그램 종료
		}
		else
		{
			// 정의되지 않은 명령은 무시하거나 메시지 출력
			continue ;
		}
	}
	return 0;
}