// 1. Include Guard 시작 (중복 인클루드 방지)
#ifndef CONTACT_HPP
# define CONTACT_HPP

// 문자열을 사용하기 위해 string 헤더 포함
# include <string>

// 2. 클래스 정의 시작 (UpperCamelCase)
class Contact
{
	// 내부에서만 사용하는 데이터 (Attributes)
	private:
		// 성, 이름, 별명, 전화번호, 비밀을 저장할 std::string 변수들
		// 관례적으로 private 변수 앞에는 '_'를 붙이기도 합니다 (예: _firstName).
		std::string _firstName;
		std::string _lastName;
		std::string _nickname;
		std::string _phoneNumber;
		std::string _darkestSecret;

		// 내부에서만 사용하는 헬퍼 함수는 private에 두는 것이 좋습니다.
		// 문자열을 10자 포맷으로 변환하는 내부 헬퍼 함수
		void	_printTruncated(std::string str) const;

	// 외부에서 접근 가능한 기능 (Member Functions)
	public:
		// 생성자: 객체가 처음 만들어질 때 호출됨
		Contact();
		// 소멸자: 객체가 사라질 때 호출됨
		~Contact();

		// 정보를 입력받아 저장하는 함수 (예: set_values)
		bool	setInfo();

		// 정보를 출력하는 함수 (예: display_summary, display_full)
		void	displaySummary(int index) const; // const: 객체의 상태(멤버 변수)를 절대 바꾸지 않겠다
		void	displayFull() const;

};

// 1. Include Guard 끝
#endif