#ifndef CURE_HPP
# define CURE_HPP

# include "AMateria.hpp"

// ────────────────────────────────────────────────────────────
// Cure: AMateria를 상속한 구체적 마테리아 클래스 (치유)
// ────────────────────────────────────────────────────────────
class Cure : public AMateria
{
	public:
		Cure();
		Cure(const Cure &other);
		Cure &operator=(const Cure &other);
		virtual ~Cure();

		virtual AMateria *clone() const;
		virtual void use(ICharacter &target);
};

#endif
