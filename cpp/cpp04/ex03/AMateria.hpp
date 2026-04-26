#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <iostream>
# include <string>

// ICharacter를 전방 선언(Forward Declaration)
// → 헤더 순환 참조를 방지하기 위해 #include 대신 사용
class ICharacter;

// ────────────────────────────────────────────────────────────
// AMateria: 마테리아의 추상 기반 클래스
// 구체적인 마테리아 타입(Ice, Cure)의 공통 인터페이스를 정의
// ────────────────────────────────────────────────────────────
class AMateria
{
protected:
    std::string type; // 마테리아 종류 ("ice", "cure" 등)

public:
    // ── Orthodox Canonical Form ──
    AMateria();
    AMateria(std::string const &type);
    AMateria(const AMateria &other);
    AMateria &operator=(const AMateria &other);
    virtual ~AMateria();

    // ── type getter ──
    std::string const &getType() const; // const 참조 반환으로 복사 없이 읽기

    // ── 순수 가상 함수: 자식 클래스에서 반드시 구현 ──

    // clone(): 자신과 동일한 타입의 새 객체를 동적으로 만들어 반환
    // → Prototype 패턴: 타입을 모르더라도 복사본을 만들 수 있음
    virtual AMateria *clone() const = 0;

    // use(): 마테리아를 사용해 대상(target)에게 효과 적용
    virtual void use(ICharacter &target);
};

#endif
