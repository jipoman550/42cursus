#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include "ScavTrap.hpp"
# include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap
{
	private:
		std::string _name; // DiamondTrap's own name

	public:
		// Orthodox Canonical Form
		DiamondTrap();
		DiamondTrap(std::string name);
		DiamondTrap(const DiamondTrap& other);
		DiamondTrap& operator=(const DiamondTrap& other);
		~DiamondTrap();

		// 특별 함수
		using ScavTrap::attack; // ScavTrap의 attack 사용 명시
		void whoAmI();
};

#endif
