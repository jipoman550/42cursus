#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

// ────────────────────────────────────────────────────────────
// Animal: ex01의 기반 클래스 (ex00과 동일하나 Brain 추가 예정)
// ────────────────────────────────────────────────────────────
class Animal
{
protected:
    std::string type;

public:
    Animal();
    Animal(const Animal &other);
    Animal &operator=(const Animal &other);
    virtual ~Animal();

    virtual void makeSound() const;
    std::string  getType() const;
};

#endif
