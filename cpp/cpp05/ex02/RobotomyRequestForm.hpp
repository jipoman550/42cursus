#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include "AForm.hpp"
# include <cstdlib> // std::rand, std::srand

class RobotomyRequestForm : public AForm {
private:
	std::string _target;

public:
	RobotomyRequestForm();
	RobotomyRequestForm(const std::string& target);
	RobotomyRequestForm(const RobotomyRequestForm& other);
	RobotomyRequestForm& operator=(const RobotomyRequestForm& other);
	virtual ~RobotomyRequestForm();

	// 순수 가상 함수 구현 (오버라이딩)
	// 50% 확률로 로봇 수술을 성공시키거나 실패시킵니다.
	virtual void execute(Bureaucrat const & executor) const;
};

#endif