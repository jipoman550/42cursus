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
	std::cout << "=== [Correct polymorphic test - using virtual] ===" << std::endl;

	// Animal* 포인터로 Dog와 Cat 객체를 가리킴 (Upcasting)
	// → 이것이 다형성의 핵심! 부모 타입 포인터로 자식 객체를 다룸
	const Animal *a= new Animal();
	const Animal *dog = new Dog();
	const Animal *cat = new Cat();

	std::cout << "\n--- Check type ---" << std::endl;
	std::cout << "a->getType(): " << a->getType() << std::endl;
	std::cout << "dog->getType(): " << dog->getType() << std::endl;
	std::cout << "cat->getType(): " << cat->getType() << std::endl;

	std::cout << "\n--- Sound output (dynamic binding) ---" << std::endl;
	// dog와 cat은 Animal* 타입이지만, virtual 덕분에
	// 실제 객체(Dog, Cat)의 makeSound()가 호출됨!
	a->makeSound();
	dog->makeSound(); // Dog::makeSound() 호출
	cat->makeSound(); // Cat::makeSound() 호출

	std::cout << "\n--- delete: Child destructors are also called thanks to the virtual destructor ---" << std::endl;
	delete a;
	delete dog; // Dog::~Dog() → Animal::~Animal() 순으로 호출
	delete cat; // Cat::~Cat() → Animal::~Animal() 순으로 호출

	std::cout << "\n=== [Incorrect polymorphism test - no virtual] ===" << std::endl;

	const WrongAnimal *wrongCat = new WrongCat();

	std::cout << "\n--- Check type ---" << std::endl;
	std::cout << "wrongCat->getType(): " << wrongCat->getType() << std::endl;

	std::cout << "\n--- Sound output (static binding) ---" << std::endl;
	// WrongAnimal* 이므로 virtual이 없어 항상 WrongAnimal::makeSound() 호출
	// → WrongCat::makeSound()는 절대 불리지 않음!
	wrongCat->makeSound();

	std::cout << "\n--- delete: Since there is no virtual destructor, only WrongAnimal::~WrongAnimal() is called ---" << std::endl;
	delete wrongCat; // WrongCat::~WrongCat() 는 호출 안 됨! → 메모리 누수 위험

	return (0);
}
