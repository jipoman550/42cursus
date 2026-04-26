#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include "IMateriaSource.hpp"

// ────────────────────────────────────────────────────────────
// MateriaSource: IMateriaSource 인터페이스를 구현한 마테리아 상점
// 최대 4개의 마테리아를 기억하고 복제해 제공
// ────────────────────────────────────────────────────────────
class MateriaSource : public IMateriaSource
{
private:
    AMateria *templates[4]; // 기억하는 마테리아 템플릿 (최대 4개)

public:
    MateriaSource();
    MateriaSource(const MateriaSource &other);
    MateriaSource &operator=(const MateriaSource &other);
    virtual ~MateriaSource();

    // ── IMateriaSource 인터페이스 구현 ──
    virtual void      learnMateria(AMateria *m);
    virtual AMateria *createMateria(std::string const &type);
};

#endif
