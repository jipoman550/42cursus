#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap
{
	public:
		// Orthodox Canonical Form
		FragTrap();                                  // 기본 생성자
		FragTrap(std::string name);                  // 매개변수 생성자
		FragTrap(const FragTrap& other);             // 복사 생성자
		FragTrap& operator=(const FragTrap& other);  // 대입 연산자 오버로딩
		~FragTrap();                                 // 소멸자

		// 특수 능력 함수
		void highFivesGuys(void);
};

#endif
