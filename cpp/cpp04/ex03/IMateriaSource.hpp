#ifndef IMATERIASOURCE_HPP
# define IMATERIASOURCE_HPP

# include "AMateria.hpp"

// ────────────────────────────────────────────────────────────
// IMateriaSource: 마테리아를 생산하는 소스의 인터페이스
// 마테리아를 기억하고, 이름으로 복제해 내줄 수 있는 "마테리아 상점" 역할
// ────────────────────────────────────────────────────────────
class IMateriaSource
{
public:
    virtual ~IMateriaSource() {}

    // learnMateria(): 마테리아를 기억함 (최대 4개)
    virtual void learnMateria(AMateria *m) = 0;

    // createMateria(): type 문자열로 기억된 마테리아를 복제해 반환
    // 모르는 타입이면 0(NULL) 반환
    virtual AMateria *createMateria(std::string const &type) = 0;
};

#endif
