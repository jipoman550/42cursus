#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain: Call default constructor" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		this->ideas[i] = "";
	}
}

Brain::Brain(const Brain &other)
{
	std::cout << "Brain: Call copy constructor" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		this->ideas[i] = other.ideas[i];
	}
}

Brain &Brain::operator=(const Brain &other)
{
	std::cout << "Brain: Call assignment operator" << std::endl;
	if (this != &other)
	{
		for (int i = 0; i < 100; i++)
		{
			this->ideas[i] = other.ideas[i];
		}
	}
	return (*this);
}

Brain::~Brain()
{
	std::cout << "Brain: Destructor called" << std::endl;
}

void Brain::setIdea(int index, const std::string &idea)
{
	if (index >= 0 && index < 100)
	{
		this->ideas[index] = idea;
	}
}

std::string Brain::getIdea(int index) const
{
	if (index >= 0 && index < 100)
	{
		return (this->ideas[index]);
	}
	return ("");
}
