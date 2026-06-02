#include "Bureaucrat.hpp"
#include "Form.hpp" // Form 객체의 메서드를 사용하기 위해 실제 헤더를 포함합니다.

Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) {
}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
	if (grade < 1) {
		throw Bureaucrat::GradeTooHighException();
	}
	if (grade > 150) {
		throw Bureaucrat::GradeTooLowException();
	}
	this->_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade) {
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
	if (this != &other) {
		this->_grade = other._grade;
	}
	return *this;
}

Bureaucrat::~Bureaucrat() {
}

const std::string& Bureaucrat::getName() const { return this->_name; }
int Bureaucrat::getGrade() const { return this->_grade; }

void Bureaucrat::incrementGrade() {
	if (this->_grade - 1 < 1) {
		throw Bureaucrat::GradeTooHighException();
	}
	this->_grade--;
}

void Bureaucrat::decrementGrade() {
	if (this->_grade + 1 > 150) {
		throw Bureaucrat::GradeTooLowException();
	}
	this->_grade++;
}

// signForm 구현
// try-catch 블록을 사용해 Form::beSigned() 내부에서 발생한 예외를 감지합니다.
void Bureaucrat::signForm(Form& form) {
	try {
		// 서류 객체의 beSigned 함수를 호출해 자기 자신을 전달
		form.beSigned(*this);
		// 예외가 발생하지 않았다면 서명에 성공한 것입니다.
		std::cout << this->_name << " signed " << form.getName() << std::endl;
	} catch (const std::exception& e) {
		// 권한 부족 등의 이유로 예외가 던져진 경우 실패 메시지와 이유를 출력합니다.
		std::cout << this->_name << " couldn't sign " << form.getName()
		          << " because " << e.what() << std::endl;
	}
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return "Bureaucrat grade is too high! (Must be between 1 and 150)";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
	return "Bureaucrat grade is too low! (Must be between 1 and 150)";
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat) {
	os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
	return os;
}
