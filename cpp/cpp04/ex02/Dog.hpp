#ifndef DOG_HPP
# define DOG_HPP

# include "AAnimal.hpp"
# include "Brain.hpp"

// ────────────────────────────────────────────────────────────
// Dog: AAnimal(추상 클래스)을 상속받아 makeSound()를 구현한 클래스
// makeSound()를 구현했으므로 Dog는 인스턴스화 가능!
// ────────────────────────────────────────────────────────────
class Dog : public AAnimal
{
private:
    Brain *brain;

public:
    Dog();
    Dog(const Dog &other);
    Dog &operator=(const Dog &other);
    virtual ~Dog();

    virtual void makeSound() const; // 순수 가상 함수 구현 (필수!)
    Brain       *getBrain() const;
};

#endif
