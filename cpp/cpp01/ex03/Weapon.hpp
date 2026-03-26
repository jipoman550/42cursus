#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>

// Weapon 클래스 선언
class Weapon {
	private:
		// 무기의 종류를 저장하는 문자열
		std::string _type;

	public:
		// 생성자: 무기 종류(type)를 받아서 초기화
		Weapon(std::string type);
		// 소멸자
		~Weapon();

		// 무기 종류(type)를 반환하는 함수.
		// const 참조자를 반환하여 외부에서의 수정을 막고, 불필요한 복사를 방지합니다.
		// const 함수로 선언하여 이 함수가 멤버 변수를 변경하지 않음을 명시합니다.
		const std::string& getType() const;

		// 무기 종류(type)를 설정하는 함수.
		void setType(std::string type);
};

#endif
