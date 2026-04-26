#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

// ────────────────────────────────────────────────────────────
// Dog: ex01에서 Brain* 멤버를 동적으로 소유하는 클래스
// ────────────────────────────────────────────────────────────
class Dog : public Animal
{
private:
    Brain *brain; // 힙(heap)에 동적 할당된 Brain 객체 포인터

public:
    Dog();
    Dog(const Dog &other);             // 깊은 복사 필요!
    Dog &operator=(const Dog &other);  // 깊은 복사 필요!
    virtual ~Dog();                    // delete brain 처리

    virtual void makeSound() const;
    Brain       *getBrain() const; // brain 포인터 반환 (외부 접근용)
};

#endif
