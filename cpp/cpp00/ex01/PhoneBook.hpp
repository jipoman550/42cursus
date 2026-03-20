#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp" // Contact 객체를 사용하기 위해 필요

class PhoneBook
{
	private:
		// 1. Contact 객체 8개를 담는 정적 배열
		Contact	_contacts[8];

		// 2. 순환 저장을 위한 인덱스 카운터
		// 팁: 추가된 총 횟수를 기록하면 (count % 8)로 저장 위치를 결정할 수 있습니다.
		int	_index;
		int	_totalCount;	// 현재 저장된 실제 연락처 개수 (SEARCH 제한용)

	public:
		// 3. 생성자 및 소멸자
		PhoneBook();
		~PhoneBook();

		// 4. 주요 기능 함수들
		void	addContact();		// ADD 명령 처리
		void	searchContact() const;	// SEARCH 명령 처리
};

#endif