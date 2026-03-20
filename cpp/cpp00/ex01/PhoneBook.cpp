#include <iostream>
#include <iomanip>		// std::setw (정렬) 등을 위해 필요
#include "PhoneBook.hpp"

// 1. 생성자: 프로그램 시작 시 변수 초기화
PhoneBook::PhoneBook()
{
	this->_index = 0;
	this->_totalCount = 0;
}

// 2. 소멸자: 프로그램 종료 시 (지금은 할 일 없음)
PhoneBook::~PhoneBook() {}

// 3. ADD 기능 구현
void PhoneBook::addContact()
{
	// 1. 현재 저장할 위치 계산 (0~7 사이를 뱅글뱅글 돎)
	int i = this->_index % 8;

	// 2. Contact 객체에게 "입력받아라"라고 시킴
	// (Contact 클래스에 정보를 입력받는 함수를 미리 만들어둬야 함)
	if (this->_contacts[i].setInfo() == false)
	{
		// 만약 입력 도중 Ctrl+D가 눌렸다면 중단
		return ;
	}

	// 3. 인덱스 증가 및 전체 개수 업데이트
	this->_index++;
	if (this->_totalCount < 8)
	{
		this->_totalCount++;
	}

	std::cout << "Successfully added!" << std::endl;
}

// 4. SEARCH 기능 구현
void PhoneBook::searchContact() const
{
	if (this->_totalCount == 0)
	{
		std::cout << "PhoneBook is empty!" << std::endl;
		return;
	}

	// 1. 헤더 출력 (index, first name, last name, nickname)
	// std::setw(10)를 사용해 칸을 맞춥니다.
	std::cout << "|" << std::setw(10) << "index" << "|";
	std::cout << std::setw(10) << "first name" << "|";
	std::cout << std::setw(10) << "last name" << "|";
	std::cout << std::setw(10) << "nickname" << "|" << std::endl;

	// 2. 루프를 돌며 각 Contact의 요약 정보 출력
	for (int i = 0; i < this->_totalCount; i++) // for([초기화];[조건식];[증감식])
	{
		this->_contacts[i].displaySummary(i);
	}

	// 3. 인덱스 입력 받기
	std::string input;
	std::cout << "Enter index to display details: ";
	if (!std::getline(std::cin, input))
	{
		return ; // Ctrl+D 처리
	}

	// 유효성 검사: 한 자리 숫자이고, 현재 저장된 개수 범위 내인지 확인
	if (input.length() == 1 && input[0] >= '0' && input[0] < '0' + this->_totalCount)
	{
		int idx = input[0] - '0';
		this->_contacts[idx].displayFull(); // 상세 정보 출력 호출
	}
	else
	{
		std::cout << "Invalid index! Please enter a valid number from the list." << std::endl;
	}
}