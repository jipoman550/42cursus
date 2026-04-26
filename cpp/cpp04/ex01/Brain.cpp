#include "Brain.hpp"

// ────────────────────────────────────────────────────────────
// Brain 클래스 구현
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: 모든 아이디어를 빈 문자열로 초기화 ──
Brain::Brain()
{
    std::cout << "Brain: 기본 생성자 호출" << std::endl;
    for (int i = 0; i < 100; i++)
        this->ideas[i] = ""; // 각 슬롯 초기화
}

// ── 복사 생성자: 깊은 복사(Deep Copy)
//    배열의 각 원소를 하나씩 복사 → 주소가 아니라 값이 복사됨
Brain::Brain(const Brain &other)
{
    std::cout << "Brain: 복사 생성자 호출 (깊은 복사)" << std::endl;
    for (int i = 0; i < 100; i++)
        this->ideas[i] = other.ideas[i]; // 문자열 값 자체를 복사
}

// ── 대입 연산자: 깊은 복사 ──
Brain &Brain::operator=(const Brain &other)
{
    std::cout << "Brain: 대입 연산자 호출 (깊은 복사)" << std::endl;
    if (this != &other)
    {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = other.ideas[i];
    }
    return (*this);
}

// ── 소멸자 ──
Brain::~Brain()
{
    std::cout << "Brain: 소멸자 호출" << std::endl;
}

// ── 아이디어 설정: 인덱스 범위 검사 후 저장 ──
void Brain::setIdea(int index, const std::string &idea)
{
    if (index >= 0 && index < 100) // 범위 초과 방지
        this->ideas[index] = idea;
}

// ── 아이디어 읽기: 인덱스 범위 검사 후 반환 ──
std::string Brain::getIdea(int index) const
{
    if (index >= 0 && index < 100)
        return (this->ideas[index]);
    return (""); // 범위 초과 시 빈 문자열 반환
}
