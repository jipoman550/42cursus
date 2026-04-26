#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"

// ────────────────────────────────────────────────────────────
// Dog 클래스: Animal을 public 상속받는 자식 클래스
// ────────────────────────────────────────────────────────────
class Dog : public Animal
{
public:
    // ── Orthodox Canonical Form (정통 표준 형식) 4가지 ──
    Dog();                              // 기본 생성자
    Dog(const Dog &other);             // 복사 생성자
    Dog &operator=(const Dog &other);  // 대입 연산자
    virtual ~Dog();                    // 가상 소멸자

    // ── makeSound() 재정의: 개 소리를 출력 ──
    virtual void makeSound() const;
};

#endif
