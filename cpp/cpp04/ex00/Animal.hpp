#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

// ────────────────────────────────────────────────────────────
// Animal 클래스: 모든 동물의 공통 기반(Base) 클래스
// virtual 키워드를 사용해 동적 바인딩을 가능하게 함
// ────────────────────────────────────────────────────────────
class Animal
{
	protected:
		std::string type; // 동물의 종류를 저장하는 변수 (자식 클래스에서 접근 가능)

	public:
		// ── 기본 생성자: type을 "Animal"로 초기화 ──
		Animal();

		// ── 복사 생성자: 다른 Animal 객체를 복사 ──
		Animal(const Animal &other);

		// ── 대입 연산자 ──
		Animal &operator=(const Animal &other);

		// ── 가상 소멸자(Virtual Destructor) ──
		//    다형성(Polymorphism)을 사용할 때 반드시 virtual로 선언해야 함
		//    그렇지 않으면 자식 클래스의 소멸자가 호출되지 않아 메모리 누수 발생!
		virtual ~Animal();

		// ── virtual makeSound(): 자식 클래스에서 재정의(override)할 수 있음 ──
		//    'virtual' 이 없으면 정적 바인딩 → 항상 부모의 함수가 호출됨
		//    'virtual' 이 있으면 동적 바인딩 → 실제 객체 타입의 함수가 호출됨
		virtual void makeSound() const;

		// ── type getter ──
		std::string getType() const;
};

#endif
