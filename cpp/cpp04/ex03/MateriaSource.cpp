#include "MateriaSource.hpp"

// ────────────────────────────────────────────────────────────
// MateriaSource 클래스 구현
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: 모든 템플릿 슬롯을 NULL로 초기화 ──
MateriaSource::MateriaSource()
{
	std::cout << "MateriaSource: Default constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		this->templates[i] = NULL;
	}
}

// ── 복사 생성자: 템플릿 마테리아를 clone()으로 깊은 복사 ──
MateriaSource::MateriaSource(const MateriaSource &other)
{
	std::cout << "MateriaSource: Copy constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (other.templates[i] != NULL)
		{
			this->templates[i] = other.templates[i]->clone();
		}
		else
		{
			this->templates[i] = NULL;
		}
	}
}

// ── 대입 연산자 ──
MateriaSource &MateriaSource::operator=(const MateriaSource &other)
{
	std::cout << "MateriaSource: Assignment operator called" << std::endl;
	if (this != &other)
	{
		for (int i = 0; i < 4; i++)
		{
			delete this->templates[i];
			this->templates[i] = NULL;
		}
		for (int i = 0; i < 4; i++)
		{
			if (other.templates[i] != NULL)
			{
				this->templates[i] = other.templates[i]->clone();
			}
		}
	}
	return (*this);
}

// ── 소멸자: 기억하고 있던 마테리아 템플릿 해제 ──
MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4; i++)
	{
		delete this->templates[i];
	}
	std::cout << "MateriaSource: Destructor called" << std::endl;
}

// ── learnMateria(): 마테리아를 기억 (빈 슬롯에 저장) ──
// 주의: 전달받은 포인터 자체를 저장함 (clone하지 않음)
// → MateriaSource가 소유권을 가짐
void MateriaSource::learnMateria(AMateria *m)
{
	if (m == NULL)
	{
		return ;
	}
	for (int i = 0; i < 4; i++)
	{
		if (this->templates[i] == NULL)
		{
			this->templates[i] = m; // 포인터 소유
			std::cout << "MateriaSource: learned [" << m->getType() << "] at slot " << i << std::endl;
			return ;
		}
	}
	delete m;
	std::cout << "MateriaSource: slots are full! Cannot learn more Materia." << std::endl;
}

// ── createMateria(): type과 일치하는 마테리아를 clone()해서 반환 ──
// type을 모르면 NULL(0) 반환
AMateria *MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < 4; i++)
	{
		// 저장된 마테리아 중 type이 일치하는 것을 찾아 복제 반환
		if (this->templates[i] != NULL && this->templates[i]->getType() == type)
		{
			std::cout << "MateriaSource: creating [" << type << "]" << std::endl;
			return (this->templates[i]->clone()); // 새 객체 반환
		}
	}
	std::cout << "MateriaSource: unknown type [" << type << "]" << std::endl;
	return (NULL); // C++98: nullptr 대신 NULL 또는 0 사용
}