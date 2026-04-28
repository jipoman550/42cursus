#ifndef AANIMAL_HPP
# define AANIMAL_HPP

# include <iostream>
# include <string>

// ────────────────────────────────────────────────────────────
// AAnimal: 추상 클래스 (Abstract Class)
// ────────────────────────────────────────────────────────────
// 'A' 접두사는 42 과제 규칙상 추상 클래스임을 표시하는 관례
//
// 순수 가상 함수(Pure Virtual Function)를 하나 이상 포함하면
// 이 클래스는 '추상 클래스'가 되어 직접 인스턴스화 불가!
// → new AAnimal() 하면 컴파일 에러 발생
// ────────────────────────────────────────────────────────────
class AAnimal
{
	protected:
		std::string type;

	public:
		AAnimal();
		AAnimal(const AAnimal &other);
		AAnimal &operator=(const AAnimal &other);
		virtual ~AAnimal(); // virtual 소멸자 유지

		// ── 순수 가상 함수(Pure Virtual Function): = 0 이 핵심! ──
		// 이 함수는 자식 클래스에서 반드시 구현해야 함
		// 구현하지 않으면 자식 클래스도 추상 클래스가 되어 인스턴스화 불가
		virtual void makeSound() const = 0;

		std::string getType() const;
};

#endif
