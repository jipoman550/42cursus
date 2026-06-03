#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include "AForm.hpp"

class PresidentialPardonForm : public AForm {
private:
	std::string _target;

public:
	PresidentialPardonForm();
	PresidentialPardonForm(const std::string& target);
	PresidentialPardonForm(const PresidentialPardonForm& other);
	PresidentialPardonForm& operator=(const PresidentialPardonForm& other);
	virtual ~PresidentialPardonForm();

	// 순수 가상 함수 구현 (오버라이딩)
	// 자포드 비블브록스의 사면 메시지를 출력합니다.
	virtual void execute(Bureaucrat const & executor) const;
};

#endif