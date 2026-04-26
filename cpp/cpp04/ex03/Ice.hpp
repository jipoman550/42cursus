#ifndef ICE_HPP
# define ICE_HPP

# include "AMateria.hpp"

// ────────────────────────────────────────────────────────────
// Ice: AMateria를 상속한 구체적 마테리아 클래스 (얼음)
// ────────────────────────────────────────────────────────────
class Ice : public AMateria
{
public:
    Ice();
    Ice(const Ice &other);
    Ice &operator=(const Ice &other);
    virtual ~Ice();

    // ── clone(): 자신과 같은 Ice 객체를 heap에 새로 만들어 반환 ──
    //    Prototype 패턴 → 타입을 몰라도 복사본 생성 가능
    virtual AMateria *clone() const;

    // ── use(): 얼음 마법 효과 출력 ──
    virtual void use(ICharacter &target);
};

#endif
