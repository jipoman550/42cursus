#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"

// ────────────────────────────────────────────────────────────
// Cat 클래스: Animal을 public 상속받는 자식 클래스
// ────────────────────────────────────────────────────────────
class Cat : public Animal
{
	public:
		Cat();								// 기본 생성자
		Cat(const Cat &other);				// 복사 생성자
		Cat &operator=(const Cat &other);	// 대입 연산자
		virtual ~Cat();						// 가상 소멸자

		// ── makeSound() 재정의: 고양이 소리를 출력 ──
		virtual void makeSound() const;
};

#endif
