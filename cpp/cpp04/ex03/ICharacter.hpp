#ifndef ICHARACTER_HPP
# define ICHARACTER_HPP

# include <string>

// AMateria를 전방 선언
class AMateria;

// ────────────────────────────────────────────────────────────
// ICharacter: 캐릭터 인터페이스
// C++98에는 interface 키워드가 없으므로
// 순수 가상 함수로만 구성된 클래스로 인터페이스를 표현
//
// 'I' 접두사는 42 과제 규칙상 인터페이스임을 표시하는 관례
// ────────────────────────────────────────────────────────────
class ICharacter
{
public:
    // ── 순수 가상 소멸자: 인터페이스도 가상 소멸자가 필요 ──
    virtual ~ICharacter() {}

    // ── 순수 가상 함수들: 구현 클래스가 반드시 정의해야 함 ──
    virtual std::string const &getName() const = 0;

    // equip(): 슬롯(0~3)에 마테리아를 장착
    virtual void equip(AMateria *m) = 0;

    // unequip(): 슬롯에서 마테리아를 해제 (delete 하지 않음!)
    virtual void unequip(int idx) = 0;

    // use(): 슬롯의 마테리아를 target에게 사용
    virtual void use(int idx, ICharacter &target) = 0;
};

#endif
