#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

int main()
{
	// HumanA 테스트 블록
	{
		// "crude spiked club" 타입의 Weapon 객체 생성
		Weapon club = Weapon("crude spiked club");

		// HumanA "Bob" 생성, 생성자에 club을 참조자로 전달
		// Bob은 생성 시점부터 항상 club을 가지고 있습니다.
		HumanA bob("Bob", club);
		bob.attack();

		// 원본 Weapon 객체의 타입을 변경
		club.setType("some other type of club");
		// Bob이 참조하고 있는 무기의 타입도 함께 변경되는 것을 확인
		bob.attack();
	}
	// HumanB 테스트 블록
	{
		// "crude spiked club" 타입의 Weapon 객체 생성
		Weapon club = Weapon("crude spiked club");

		// HumanB "Jim" 생성. 처음에는 무기가 없는 상태
		HumanB jim("Jim");
		jim.attack(); // "has no weapon to attack" 메시지가 나와야 함

		// setWeapon을 통해 Jim에게 club을 장착
		jim.setWeapon(club);
		jim.attack();

		// 원본 Weapon 객체의 타입을 변경
		club.setType("some other type of club");
		// Jim이 가리키고 있는 무기의 타입도 함께 변경되는 것을 확인
		jim.attack();
	}
	return 0;
}
