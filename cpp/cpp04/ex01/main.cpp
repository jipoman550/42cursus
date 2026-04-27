#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

// ────────────────────────────────────────────────────────────
// main: Brain의 깊은 복사와 메모리 관리를 테스트
// ────────────────────────────────────────────────────────────
int main()
{
	std::cout << "=== [동물 배열 테스트] ===" << std::endl;

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

	std::cout << "\n--- 소리 출력 ---" << std::endl;
	for (int i = 0; i < SIZE; i++)
	{
		animals[i]->makeSound(); // 동적 바인딩으로 실제 타입의 소리 호출
	}

	std::cout << "\n--- 배열 delete ---" << std::endl;
	for (int i = 0; i < SIZE; i++)
	{
		delete animals[i]; // virtual 소멸자 덕분에 자식 소멸자(brain delete 포함)도 호출됨
	}

	std::cout << "\n=== [깊은 복사 테스트] ===" << std::endl;

	Dog original;
	// original의 brain 첫 번째 아이디어 설정
	original.getBrain()->setIdea(0, "뼈다귀를 찾아야겠다");
	original.getBrain()->setIdea(1, "산책가고 싶다");

	std::cout << "\n--- 복사 생성 ---" << std::endl;
	Dog copy(original); // 복사 생성자 호출 → 깊은 복사

	std::cout << "\n--- 복사 전 아이디어 비교 ---" << std::endl;
	std::cout << "original[0]: " << original.getBrain()->getIdea(0) << std::endl;
	std::cout << "copy[0]:     " << copy.getBrain()->getIdea(0) << std::endl;

	// 복사본의 아이디어를 변경해도 원본에 영향 없어야 함 (깊은 복사 검증)
	copy.getBrain()->setIdea(0, "고양이를 쫓아야겠다");

	std::cout << "\n--- copy 아이디어 변경 후 비교 ---" << std::endl;
	std::cout << "original[0]: " << original.getBrain()->getIdea(0) << std::endl; // 변경 없어야 함
	std::cout << "copy[0]:     " << copy.getBrain()->getIdea(0) << std::endl;     // 새 값

	std::cout << "\n--- 소멸자 호출 (brain도 함께 해제됨) ---" << std::endl;
	// 스코프 종료 시 자동으로 original과 copy의 소멸자 호출

	return (0);
}
