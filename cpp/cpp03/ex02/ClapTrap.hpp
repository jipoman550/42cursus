#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>
# include <string>

class ClapTrap
{
	protected:
		std::string _name;
		unsigned int _hitPoints;
		unsigned int _energyPoints;
		unsigned int _attackDamage;

	public:
		// Orthodox Canonical Form
		ClapTrap();                                  // 기본 생성자
		ClapTrap(std::string name);                  // 매개변수 생성자
		ClapTrap(const ClapTrap& other);             // 복사 생성자
		ClapTrap& operator=(const ClapTrap& other);  // 대입 연산자 오버로딩
		~ClapTrap();                                 // 소멸자

		// 기능 함수
		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

#endif
