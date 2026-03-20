#include "Contact.hpp"
#include <iostream>
#include <iomanip>		// std::setw (정렬) 등을 위해 필요

Contact::Contact() {}

Contact::~Contact() {}

bool	Contact::setInfo()
{
	std::string fields[5] = {"First Name", "Last Name", "Nickname", "Phone Number", "Darkest Secret"};
	std::string *targets[5] = {&_firstName, &_lastName, &_nickname, &_phoneNumber, &_darkestSecret};

	for (int i = 0; i < 5; i++)
	{
		while (true)
		{
			std::cout << "Enter " << fields[i] << ": ";
			if (!std::getline(std::cin, *targets[i]))
			{
				return (false); // Ctrl+D 입력 시 즉시 false 반환
			}
			if (!targets[i]->empty())
			{
				break ; // 비어있지 않으면 루프 탈출
			}
			std::cout << "Error: Field cannot be empty." << std::endl;
		}
	}
	return (true); // 모든 입력이 성공하면 true 반환
}

void	Contact::displaySummary(int index) const
{
	std::cout << "|" << std::setw(10) << index << "|";
	_printTruncated(_firstName); std::cout << "|";
	_printTruncated(_lastName); std::cout << "|";
	_printTruncated(_nickname); std::cout << "|" << std::endl;
}

// 이 함수가 Contact 클래스 소속임을 명시 (Contact::)
void	Contact::_printTruncated(std::string str) const
{
	if (str.length() > 10)
	{
		std::cout << str.substr(0, 9) << ".";
	}
	else
	{
		std::cout << std::setw(10) << str;
	}
}

// Contact.cpp에 추가
void	Contact::displayFull() const
{
	std::cout << "First Name     : " << this->_firstName << std::endl;
	std::cout << "Last Name      : " << this->_lastName << std::endl;
	std::cout << "Nickname       : " << this->_nickname << std::endl;
	std::cout << "Phone Number   : " << this->_phoneNumber << std::endl;
	std::cout << "Darkest Secret : " << this->_darkestSecret << std::endl;
}