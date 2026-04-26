#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

# include "WrongAnimal.hpp"

// ────────────────────────────────────────────────────────────
// WrongCat: WrongAnimal을 상속받은 잘못된 예시 클래스
// virtual이 없으니 포인터로 다루면 WrongAnimal의 함수가 불림
// ────────────────────────────────────────────────────────────
class WrongCat : public WrongAnimal
{
public:
    WrongCat();
    WrongCat(const WrongCat &other);
    WrongCat &operator=(const WrongCat &other);
    ~WrongCat(); // virtual 없음

    // 이 함수는 WrongAnimal 포인터로 호출하면 절대 불리지 않음!
    void makeSound() const;
};

#endif
