#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
	public:
		// Orthodox Canonical Form
		ScavTrap();									// 기본 생성자
		ScavTrap(std::string name);					// 매개변수 생성자
		ScavTrap(const ScavTrap& other);			// 복사 생성자
		ScavTrap& operator=(const ScavTrap& other);	// 대입 연산자 오버로딩
		virtual ~ScavTrap();						// 소멸자

		// 멤버 함수 (ClapTrap 기능 덮어쓰기)
		void attack(const std::string& target);

		// 특수 능력 함수
		void guardGate();
};

#endif
