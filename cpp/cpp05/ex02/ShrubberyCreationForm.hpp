#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include "AForm.hpp"
# include <fstream>

class ShrubberyCreationForm : public AForm {
private:
	std::string _target;

public:
	ShrubberyCreationForm();
	// 타겟을 받는 매개변수 생성자 (주로 사용됨)
	ShrubberyCreationForm(const std::string& target);
	ShrubberyCreationForm(const ShrubberyCreationForm& other);
	ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
	virtual ~ShrubberyCreationForm();

	// 순수 가상 함수 구현 (오버라이딩)
	// ASCII 트리를 파일에 생성하는 역할을 합니다.
	virtual void execute(Bureaucrat const & executor) const;
};

#endif