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
    // AAnimal a; // 에러! 추상 클래스는 인스턴스화 불가

    std::cout << "=== [추상 클래스 테스트] ===" << std::endl;
    std::cout << "AAnimal 직접 생성 불가 (컴파일 에러) → Dog와 Cat만 생성 가능" << std::endl;

    // AAnimal* 포인터를 통해 Dog와 Cat 다형적으로 사용
    const AAnimal *dog = new Dog();
    const AAnimal *cat = new Cat();

    std::cout << "\n--- 소리 출력 ---" << std::endl;
    dog->makeSound(); // Dog::makeSound() 동적 바인딩
    cat->makeSound(); // Cat::makeSound() 동적 바인딩

    std::cout << "\n--- delete ---" << std::endl;
    delete dog;
    delete cat;

    return (0);
}
