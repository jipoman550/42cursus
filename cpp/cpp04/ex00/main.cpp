#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

// ────────────────────────────────────────────────────────────
// main: 다형성(Polymorphism)의 동작을 실제로 확인하는 테스트
// ────────────────────────────────────────────────────────────
int main()
{
    std::cout << "=== [올바른 다형성 테스트 - virtual 사용] ===" << std::endl;

    // Animal* 포인터로 Dog와 Cat 객체를 가리킴 (Upcasting)
    // → 이것이 다형성의 핵심! 부모 타입 포인터로 자식 객체를 다룸
    const Animal *dog = new Dog();
    const Animal *cat = new Cat();

    std::cout << "\n--- 타입 확인 ---" << std::endl;
    std::cout << "dog->getType(): " << dog->getType() << std::endl;
    std::cout << "cat->getType(): " << cat->getType() << std::endl;

    std::cout << "\n--- 소리 출력 (동적 바인딩) ---" << std::endl;
    // dog와 cat은 Animal* 타입이지만, virtual 덕분에
    // 실제 객체(Dog, Cat)의 makeSound()가 호출됨!
    dog->makeSound(); // Dog::makeSound() 호출
    cat->makeSound(); // Cat::makeSound() 호출

    std::cout << "\n--- delete: virtual 소멸자 덕분에 자식 소멸자도 호출됨 ---" << std::endl;
    delete dog; // Dog::~Dog() → Animal::~Animal() 순으로 호출
    delete cat; // Cat::~Cat() → Animal::~Animal() 순으로 호출

    std::cout << "\n=== [잘못된 다형성 테스트 - virtual 없음] ===" << std::endl;

    const WrongAnimal *wrongCat = new WrongCat();

    std::cout << "\n--- 타입 확인 ---" << std::endl;
    std::cout << "wrongCat->getType(): " << wrongCat->getType() << std::endl;

    std::cout << "\n--- 소리 출력 (정적 바인딩!) ---" << std::endl;
    // WrongAnimal* 이므로 virtual이 없어 항상 WrongAnimal::makeSound() 호출
    // → WrongCat::makeSound()는 절대 불리지 않음!
    wrongCat->makeSound();

    std::cout << "\n--- delete: virtual 소멸자 없어서 WrongAnimal::~WrongAnimal()만 호출 ---" << std::endl;
    delete wrongCat; // WrongCat::~WrongCat() 는 호출 안 됨! → 메모리 누수 위험

    return (0);
}
