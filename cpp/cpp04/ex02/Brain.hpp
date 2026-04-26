#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <string>

// Brain 클래스는 ex01과 동일 (재사용)
class Brain
{
private:
    std::string ideas[100];

public:
    Brain();
    Brain(const Brain &other);
    Brain &operator=(const Brain &other);
    ~Brain();

    void        setIdea(int index, const std::string &idea);
    std::string getIdea(int index) const;
};

#endif
