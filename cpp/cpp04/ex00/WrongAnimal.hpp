#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>
# include <string>

// ────────────────────────────────────────────────────────────
// WrongAnimal: virtual 키워드가 없는 잘못된 예시 클래스
// 다형성이 동작하지 않음을 보여주기 위한 비교용 클래스
// ────────────────────────────────────────────────────────────
class WrongAnimal
{
	protected:
		std::string type;

	public:
		WrongAnimal();
		WrongAnimal(const WrongAnimal &other);
		WrongAnimal &operator=(const WrongAnimal &other);
		~WrongAnimal(); // virtual 이 없음! → 자식 소멸자가 호출 안 됨

		// virtual 이 없음! → 항상 WrongAnimal::makeSound()가 호출됨 (정적 바인딩)
		void makeSound() const;

		std::string getType() const;
};

#endif
