#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"
# include <string>

// HumanA 클래스 선언
// HumanA는 항상 무기를 가지고 있다고 가정합니다.
class HumanA {
	private:
		// HumanA의 이름
		std::string _name;
		// HumanA가 사용하는 무기.
		// 참조자(&)를 사용합니다. HumanA는 생성될 때 반드시 무기를 가져야 하며,
		// 한 번 할당된 무기를 교체할 수 없습니다. 참조자는 NULL이 될 수 없습니다.
		Weapon& _weapon;

	public:
		// 생성자: 이름과 무기(참조자)를 받아 초기화 리스트를 통해 초기화합니다.
		HumanA(std::string name, Weapon& weapon);
		// 소멸자
		~HumanA();

		// 공격을 수행하는 함수
		void attack();
};

#endif
