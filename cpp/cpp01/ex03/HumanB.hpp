#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"
# include <string>

// HumanB 클래스 선언
// HumanB는 무기가 없을 수도 있습니다.
class HumanB {
	private:
		// HumanB의 이름
		std::string _name;
		// HumanB가 사용하는 무기.
		// 포인터(*)를 사용합니다. HumanB는 처음에는 무기가 없을 수 있으며 (NULL),
		// 나중에 무기를 할당받거나 교체할 수 있습니다.
		Weapon* _weapon;

	public:
		// 생성자: 이름만 받아 초기화합니다. 무기는 NULL 포인터로 초기화합니다.
		HumanB(std::string name);
		// 소멸자
		~HumanB();

		// 무기를 설정하는 함수
		void setWeapon(Weapon& weapon);

		// 공격을 수행하는 함수
		void attack();
};

#endif
