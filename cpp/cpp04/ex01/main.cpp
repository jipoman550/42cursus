#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

// ────────────────────────────────────────────────────────────
// main: Brain의 깊은 복사와 메모리 관리를 테스트
// ────────────────────────────────────────────────────────────
int main()
{
	std::cout << "=== [Animal Array Test] ===" << std::endl;

	// Animal 포인터 배열에 Dog와 Cat을 교대로 저장
	// → 배열의 절반은 Dog, 절반은 Cat
	const int SIZE = 4;
	Animal *animals[SIZE];

	for (int i = 0; i < SIZE / 2; i++)
	{
		animals[i] = new Dog(); // 앞 절반: Dog
	}
	for (int i = SIZE / 2; i < SIZE; i++)
	{
		animals[i] = new Cat(); // 뒤 절반: Cat
	}

	std::cout << "\n--- Output Sound ---" << std::endl;
	for (int i = 0; i < SIZE; i++)
	{
		animals[i]->makeSound(); // 동적 바인딩으로 실제 타입의 소리 호출
	}

	std::cout << "\n--- Delete Array ---" << std::endl;
	for (int i = 0; i < SIZE; i++)
	{
		delete animals[i]; // virtual 소멸자 덕분에 자식 소멸자(brain delete 포함)도 호출됨
	}

	std::cout << "\n=== [Deep Copy Test] ===" << std::endl;

	Dog original;
	// original의 brain 첫 번째 아이디어 설정
	original.getBrain()->setIdea(0, "I want to find a bone");
	original.getBrain()->setIdea(1, "I want to go for a walk");

	std::cout << "\n--- Copy Construction ---" << std::endl;
	Dog copy(original); // 복사 생성자 호출 → 깊은 복사

	std::cout << "\n--- Compare Ideas Before Copy ---" << std::endl;
	std::cout << "original[0]: " << original.getBrain()->getIdea(0) << std::endl;
	std::cout << "copy[0]:     " << copy.getBrain()->getIdea(0) << std::endl;

	// 복사본의 아이디어를 변경해도 원본에 영향 없어야 함 (깊은 복사 검증)
	copy.getBrain()->setIdea(0, "I want to chase a cat");

	std::cout << "\n--- Compare Ideas After Copy Modification ---" << std::endl;
	std::cout << "original[0]: " << original.getBrain()->getIdea(0) << std::endl; // 변경 없어야 함
	std::cout << "copy[0]:     " << copy.getBrain()->getIdea(0) << std::endl;     // 새 값

	std::cout << "\n--- Destructor Call (brain is also freed) ---" << std::endl;
	// 스코프 종료 시 자동으로 original과 copy의 소멸자 호출

	return (0);
}