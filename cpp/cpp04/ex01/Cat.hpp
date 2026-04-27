#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"

// ────────────────────────────────────────────────────────────
// Cat: ex01에서 Brain* 멤버를 동적으로 소유하는 클래스
// ────────────────────────────────────────────────────────────
class Cat : public Animal
{
	private:
		Brain *brain; // 힙(heap)에 동적 할당된 Brain 객체 포인터

	public:
		Cat();
		Cat(const Cat &other);
		Cat &operator=(const Cat &other);
		virtual ~Cat();

		virtual void makeSound() const;
		Brain *getBrain() const;
};

#endif
