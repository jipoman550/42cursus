#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "ICharacter.hpp"
# include "AMateria.hpp"

// ────────────────────────────────────────────────────────────
// Character: ICharacter 인터페이스를 구현한 구체적 캐릭터 클래스
// 4개의 마테리아 슬롯(slots)을 가짐
// ────────────────────────────────────────────────────────────
class Character : public ICharacter
{
private:
    std::string  name;        // 캐릭터 이름
    AMateria    *slots[4];    // 마테리아 슬롯 (최대 4개)

    // ── 버려진 마테리아 관리 (unequip 시 delete를 하지 않으므로 추적 필요) ──
    // 과제 조건: unequip()은 마테리아를 delete하지 않음 → 메모리 누수 방지를 위해
    // 버려진 마테리아를 따로 배열에 보관했다가 소멸자에서 정리
    AMateria    *floor[256];  // 버려진 마테리아 보관소
    int          floorCount;  // 현재 버려진 마테리아 수

public:
    Character();
    Character(std::string const &name);
    Character(const Character &other);             // 깊은 복사 필요
    Character &operator=(const Character &other);  // 깊은 복사 필요
    virtual ~Character();

    // ── ICharacter 인터페이스 구현 ──
    virtual std::string const &getName() const;
    virtual void               equip(AMateria *m);
    virtual void               unequip(int idx);
    virtual void               use(int idx, ICharacter &target);
};

#endif
