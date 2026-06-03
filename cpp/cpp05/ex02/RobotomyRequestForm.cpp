#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

// 요구 등급 설정 (Sign: 72, Exec: 45)
RobotomyRequestForm::RobotomyRequestForm()
	: AForm("RobotomyRequestForm", 72, 45), _target("default_target") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
	: AForm("RobotomyRequestForm", 72, 45), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
	: AForm(other), _target(other._target) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
	if (this != &other) {
		AForm::operator=(other);
		this->_target = other._target;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const {
	this->verifyExecution(executor); // 서명/실행 권한 검증

	std::cout << "Bzzzzzzzt... Brrrrrrrrrrrr... (Drilling noises)" << std::endl;

	if (std::rand() % 2 == 0)
		std::cout << this->_target << " has been successfully robotomized." << std::endl;
	else
		std::cout << "Robotomy failed on " << this->_target << "." << std::endl;
}