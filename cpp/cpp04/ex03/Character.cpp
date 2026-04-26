#include "Character.hpp"

// ────────────────────────────────────────────────────────────
// Character 클래스 구현
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: 모든 슬롯을 NULL로 초기화 ──
Character::Character() : name("unnamed"), floorCount(0)
{
    std::cout << "Character: 기본 생성자 호출" << std::endl;
    for (int i = 0; i < 4; i++)
        this->slots[i] = NULL; // C++98에서는 nullptr 대신 NULL 사용
    for (int i = 0; i < 256; i++)
        this->floor[i] = NULL;
}

// ── 이름 지정 생성자 ──
Character::Character(std::string const &name) : name(name), floorCount(0)
{
    std::cout << "Character: 생성자 호출 [" << this->name << "]" << std::endl;
    for (int i = 0; i < 4; i++)
        this->slots[i] = NULL;
    for (int i = 0; i < 256; i++)
        this->floor[i] = NULL;
}

// ── 복사 생성자: 슬롯의 마테리아를 깊은 복사 (clone 사용) ──
Character::Character(const Character &other) : name(other.name), floorCount(0)
{
    std::cout << "Character: 복사 생성자 호출" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        // NULL 슬롯은 NULL로, 마테리아가 있으면 clone()으로 복사
        if (other.slots[i] != NULL)
            this->slots[i] = other.slots[i]->clone();
        else
            this->slots[i] = NULL;
    }
    for (int i = 0; i < 256; i++)
        this->floor[i] = NULL;
}

// ── 대입 연산자: 기존 슬롯 해제 후 깊은 복사 ──
Character &Character::operator=(const Character &other)
{
    std::cout << "Character: 대입 연산자 호출" << std::endl;
    if (this != &other)
    {
        this->name = other.name;
        // 기존 슬롯 마테리아 해제
        for (int i = 0; i < 4; i++)
        {
            delete this->slots[i];
            this->slots[i] = NULL;
        }
        // 새 마테리아를 clone()으로 깊은 복사
        for (int i = 0; i < 4; i++)
        {
            if (other.slots[i] != NULL)
                this->slots[i] = other.slots[i]->clone();
        }
    }
    return (*this);
}

// ── 소멸자: 슬롯과 floor에 남은 마테리아 모두 해제 ──
Character::~Character()
{
    // 슬롯에 있는 마테리아 해제
    for (int i = 0; i < 4; i++)
        delete this->slots[i];
    // 버려진 마테리아(unequip 된 것들) 해제
    for (int i = 0; i < floorCount; i++)
        delete this->floor[i];
    std::cout << "Character: 소멸자 호출 [" << this->name << "]" << std::endl;
}

// ── getName(): 이름 반환 ──
std::string const &Character::getName() const
{
    return (this->name);
}

// ── equip(): 마테리아를 첫 번째 빈 슬롯에 장착 ──
void Character::equip(AMateria *m)
{
    if (m == NULL) // NULL 마테리아 장착 방지
        return ;
    for (int i = 0; i < 4; i++)
    {
        if (this->slots[i] == NULL) // 빈 슬롯 발견
        {
            this->slots[i] = m;
            std::cout << this->name << ": 슬롯 " << i
                      << "에 [" << m->getType() << "] 장착" << std::endl;
            return ;
        }
    }
    // 빈 슬롯이 없으면 아무것도 하지 않음
    std::cout << this->name << ": 슬롯이 가득 찼습니다!" << std::endl;
}

// ── unequip(): 슬롯에서 마테리아를 해제 (delete하지 않음!) ──
// 과제 규칙: unequip은 마테리아를 delete 하면 안 됨
// 해제된 마테리아를 floor 배열에 보관하여 나중에 소멸자에서 정리
void Character::unequip(int idx)
{
    if (idx < 0 || idx > 3) // 유효하지 않은 슬롯 번호 방지
        return ;
    if (this->slots[idx] == NULL) // 이미 비어있는 슬롯
        return ;
    std::cout << this->name << ": 슬롯 " << idx
              << "에서 [" << this->slots[idx]->getType() << "] 해제" << std::endl;
    // 버려진 마테리아를 floor에 보관 (delete하지 않음!)
    if (this->floorCount < 256)
        this->floor[this->floorCount++] = this->slots[idx];
    this->slots[idx] = NULL; // 슬롯을 비움
}

// ── use(): 슬롯의 마테리아를 target에게 사용 ──
void Character::use(int idx, ICharacter &target)
{
    if (idx < 0 || idx > 3) // 유효하지 않은 슬롯 번호
        return ;
    if (this->slots[idx] == NULL) // 슬롯이 비어 있음
        return ;
    // 마테리아의 use() 함수를 동적 바인딩으로 호출
    this->slots[idx]->use(target);
}
