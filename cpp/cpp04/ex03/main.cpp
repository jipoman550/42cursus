#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"

// ────────────────────────────────────────────────────────────
// main: 과제 PDF에서 요구하는 시나리오 테스트
// ────────────────────────────────────────────────────────────
int main()
{
	std::cout << "=== [Interface & Materia system test] ===" << std::endl;

	// ── IMateriaSource 인터페이스 포인터로 MateriaSource 사용 ──
	// 다형성: IMateriaSource*로 MateriaSource 객체를 다룸
	IMateriaSource *src = new MateriaSource();

	// MateriaSource에 Ice와 Cure 마테리아를 기억시킴
	// learnMateria는 소유권을 가져감 → 소멸자에서 delete 됨
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	// ── ICharacter 인터페이스 포인터로 Character 사용 ──
	ICharacter *me = new Character("me");

	// src로부터 마테리아를 복제해서 장착
	AMateria *tmp;
	tmp = src->createMateria("ice");	// Ice 복제 반환
	me->equip(tmp);						// 슬롯 0에 장착
	tmp = src->createMateria("cure");	// Cure 복제 반환
	me->equip(tmp);						// 슬롯 1에 장착

	// 알 수 없는 타입 → NULL 반환 (장착 안 됨)
	tmp = src->createMateria("fire");
	me->equip(tmp); // NULL이므로 equip 내부에서 무시됨

	// ── ICharacter 인터페이스 포인터로 두 번째 캐릭터 생성 ──
	ICharacter *bob = new Character("bob");

	std::cout << "\n--- Materia use ---" << std::endl;
	// me의 슬롯 0 (ice) → bob에게 사용
	me->use(0, *bob); // "* shoots an ice bolt at bob *"
	// me의 슬롯 1 (cure) → bob에게 사용
	me->use(1, *bob); // "* heals bob's wounds *"
	// 비어있는 슬롯 2 사용 → 아무것도 안 됨
	me->use(2, *bob);

	std::cout << "\n--- Object destruction ---" << std::endl;
	delete bob;	// Character 소멸자 → 슬롯 마테리아 해제
	delete me;	// Character 소멸자 → 슬롯 마테리아 해제
	delete src;	// MateriaSource 소멸자 → 템플릿 마테리아 해제


	std::cout << "\n=== [Deep Copy Test] ===" << std::endl;
	MateriaSource* src2 = new MateriaSource();
	src2->learnMateria(new Ice());

	Character* original = new Character("Original");
	original->equip(src2->createMateria("ice"));

	// 복사 생성자를 통한 깊은 복사
	Character* copy = new Character(*original);

	std::cout << "\n--- After Copy (Both should have Ice) ---" << std::endl;
	original->use(0, *copy);
	copy->use(0, *original);

	// 원본의 아이템을 해제해도 복사본은 유지되어야 함
	std::cout << "\n--- After Original Unequip (Copy should still have Ice) ---" << std::endl;
	original->unequip(0);
	original->use(0, *copy); // 출력 없음
	copy->use(0, *original);  // Ice 사용 메시지 출력됨

	std::cout << "\n--- Object destruction ---" << std::endl;
	delete original;
	delete copy;
	delete src2;


	std::cout << "\n=== [Inventory Limits & Edge Cases] ===" << std::endl;
	IMateriaSource* src3 = new MateriaSource();
	src3->learnMateria(new Ice());
	src3->learnMateria(new Cure());
	src3->learnMateria(new Ice());
	src3->learnMateria(new Cure());

	// 5번째 마테리아 학습 시도 (가득 참 메시지 출력 기대)
	src3->learnMateria(new Ice());

	ICharacter* me2 = new Character("me");
	for (int i = 0; i < 5; i++)
	{
		AMateria* tmp2 = src3->createMateria("ice");
		me2->equip(tmp2); // 5번째는 장착되지 않으므로 수동 delete 필요할 수도 있음 (실제 코드 로직 확인)
		if (i == 4)
		{
			delete tmp2; // 슬롯이 가득 차서 못 받은 아이템 처리
		}
	}

	// 잘못된 인덱스 접근 테스트
	std::cout << "\n--- Invalid Index Test ---" << std::endl;
	me2->use(-1, *me2);
	me2->use(4, *me2);
	me2->use(100, *me2);
	me2->unequip(-1);
	me2->unequip(4);

	std::cout << "\n--- Object destruction ---" << std::endl;
	delete me2;
	delete src3;


	std::cout << "\n=== [Unequip & Floor Leak Test] ===" << std::endl;
	IMateriaSource* src4 = new MateriaSource();
	src4->learnMateria(new Ice());

	ICharacter* me3 = new Character("me");
	AMateria* m4 = src4->createMateria("ice");
	AMateria* m5 = src4->createMateria("ice");

	me3->equip(m4);
	me3->equip(m5);

	me3->unequip(0); // m4이 floor[0]으로 이동
	me3->unequip(1); // m5가 floor[1]으로 이동

	// 이제 me를 delete 할 때 floor에 있는 m1, m2가 정상적으로 해제되어야 함
	std::cout << "\n--- Object destruction ---" << std::endl;
	delete me3;
	delete src4;

	return (0);
}
