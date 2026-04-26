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
    std::cout << "=== [ex03: Interface & Materia 시스템 테스트] ===" << std::endl;

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
    tmp = src->createMateria("ice");  // Ice 복제 반환
    me->equip(tmp);                   // 슬롯 0에 장착
    tmp = src->createMateria("cure"); // Cure 복제 반환
    me->equip(tmp);                   // 슬롯 1에 장착

    // 알 수 없는 타입 → NULL 반환 (장착 안 됨)
    tmp = src->createMateria("fire");
    me->equip(tmp); // NULL이므로 equip 내부에서 무시됨

    // ── ICharacter 인터페이스 포인터로 두 번째 캐릭터 생성 ──
    ICharacter *bob = new Character("bob");

    std::cout << "\n--- 마테리아 사용 ---" << std::endl;
    // me의 슬롯 0 (ice) → bob에게 사용
    me->use(0, *bob); // "* shoots an ice bolt at bob *"
    // me의 슬롯 1 (cure) → bob에게 사용
    me->use(1, *bob); // "* heals bob's wounds *"
    // 비어있는 슬롯 2 사용 → 아무것도 안 됨
    me->use(2, *bob);

    std::cout << "\n--- 객체 소멸 ---" << std::endl;
    delete bob;  // Character 소멸자 → 슬롯 마테리아 해제
    delete me;   // Character 소멸자 → 슬롯 마테리아 해제
    delete src;  // MateriaSource 소멸자 → 템플릿 마테리아 해제

    return (0);
}
