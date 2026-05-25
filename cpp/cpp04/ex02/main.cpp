#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

// ────────────────────────────────────────────────────────────
// main: 추상 클래스(AAnimal) 테스트
// ────────────────────────────────────────────────────────────
int main()
{
	// ── 추상 클래스 직접 인스턴스화 시도 (컴파일 에러!) ──
	// 아래 줄의 주석을 해제하면 에러 발생:
	// error: cannot declare variable 'a' to be of abstract type 'AAnimal'
	//AAnimal a; // 에러! 추상 클래스는 인스턴스화 불가

	std::cout << "=== [Abstract class test] ===" << std::endl;
	std::cout << "Cannot create animals directly (compilation error) → Only Dogs and Cats can be created" << std::endl;

	// AAnimal* 포인터를 통해 Dog와 Cat 다형적으로 사용
	const AAnimal *dog = new Dog();
	const AAnimal *cat = new Cat();

	std::cout << "\n--- Sound output ---" << std::endl;
	dog->makeSound(); // Dog::makeSound() 동적 바인딩
	cat->makeSound(); // Cat::makeSound() 동적 바인딩

	std::cout << "\n--- delete ---" << std::endl;
	delete dog;
	delete cat;

	return (0);
}
