#include "ClapTrap.hpp"

// 기본 생성자 (Orthodox Canonical Form)
// 속성을 캡슐화하고 기본 값을 초기화 리스트로 설정
ClapTrap::ClapTrap()
    : _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap " << _name << " is created by default constructor." << std::endl;
}

// 매개변수 생성자
// 이름을 인자로 받아 초기화
ClapTrap::ClapTrap(std::string name)
    : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap " << _name << " is created." << std::endl;
}

// 복사 생성자 (Orthodox Canonical Form)
// 다른 객체의 속성을 복사하여 초기화
ClapTrap::ClapTrap(const ClapTrap& other)
    : _name(other._name), _hitPoints(other._hitPoints), _energyPoints(other._energyPoints), _attackDamage(other._attackDamage)
{
    std::cout << "ClapTrap " << _name << " is copied." << std::endl;
}

// 대입 연산자 오버로딩 (Orthodox Canonical Form)
// 이미 생성된 객체에 다른 객체의 속성값을 대입
ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
    std::cout << "ClapTrap " << _name << " is assigned from " << other._name << "." << std::endl;
    if (this != &other)
    {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    return (*this);
}

// 소멸자 (Orthodox Canonical Form)
ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << _name << " is destroyed." << std::endl;
}

// 공격 함수
// 실행마다 에너지 포인트(EP) 1 소모.
// HP가 0 이하거나, 에너지가 0 이하면 동작 불가.
void ClapTrap::attack(const std::string& target)
{
    if (_hitPoints == 0)
    {
        std::cout << "ClapTrap " << _name << " cannot attack because it has no hit points left!" << std::endl;
        return ;
    }
    if (_energyPoints == 0)
    {
        std::cout << "ClapTrap " << _name << " cannot attack because it has no energy points left!" << std::endl;
        return ;
    }

    _energyPoints--; // 에너지 소모
    std::cout << "ClapTrap " << _name << " attacks " << target
              << ", causing " << _attackDamage << " points of damage!" << std::endl;
}

// 데미지 받는 함수
// HP를 amount만큼 감소. HP는 0 아래로 내려가지 않음.
// 에너지를 소모하지 않는 것이 포인트.
void ClapTrap::takeDamage(unsigned int amount)
{
    if (_hitPoints == 0)
    {
        std::cout << "ClapTrap " << _name << " is already dead!" << std::endl;
        return ;
    }

    // amount가 현재 hp보다 크면 hp를 0으로 맞춤 (언더플로우 방지)
    if (amount >= _hitPoints)
    {
        _hitPoints = 0;
    }
    else
    {
        _hitPoints -= amount;
    }
    std::cout << "ClapTrap " << _name << " takes " << amount
              << " points of damage! Current HP: " << _hitPoints << std::endl;
}

// 수리 받는 함수
// 실행마다 에너지 포인트(EP) 1 소모.
// HP를 amount만큼 회복.
void ClapTrap::beRepaired(unsigned int amount)
{
    if (_hitPoints == 0)
    {
        std::cout << "ClapTrap " << _name << " cannot be repaired because it has no hit points left!" << std::endl;
        return ;
    }
    if (_energyPoints == 0)
    {
        std::cout << "ClapTrap " << _name << " cannot be repaired because it has no energy points left!" << std::endl;
        return ;
    }

    _energyPoints--; // 에너지 소모
    _hitPoints += amount; // HP 회복
    std::cout << "ClapTrap " << _name << " is repaired for " << amount
              << " points! Current HP: " << _hitPoints << std::endl;
}
