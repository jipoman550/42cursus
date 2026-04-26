#include "Brain.hpp"

Brain::Brain()
{
    std::cout << "Brain: 기본 생성자 호출" << std::endl;
    for (int i = 0; i < 100; i++)
        this->ideas[i] = "";
}

Brain::Brain(const Brain &other)
{
    std::cout << "Brain: 복사 생성자 호출" << std::endl;
    for (int i = 0; i < 100; i++)
        this->ideas[i] = other.ideas[i];
}

Brain &Brain::operator=(const Brain &other)
{
    std::cout << "Brain: 대입 연산자 호출" << std::endl;
    if (this != &other)
    {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = other.ideas[i];
    }
    return (*this);
}

Brain::~Brain()
{
    std::cout << "Brain: 소멸자 호출" << std::endl;
}

void Brain::setIdea(int index, const std::string &idea)
{
    if (index >= 0 && index < 100)
        this->ideas[index] = idea;
}

std::string Brain::getIdea(int index) const
{
    if (index >= 0 && index < 100)
        return (this->ideas[index]);
    return ("");
}
