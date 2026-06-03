#include "Bureaucrat.hpp"
#include "AForm.hpp" // 다형성 메서드를 사용하기 위해 실제 헤더를 인클루드

Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) {}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade) {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
	if (this != &other)
		this->_grade = other._grade;
	return *this;
}

Bureaucrat::~Bureaucrat() {}

const std::string& Bureaucrat::getName() const { return this->_name; }
int Bureaucrat::getGrade() const { return this->_grade; }

void Bureaucrat::incrementGrade() {
	if (this->_grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException();
	this->_grade--;
}

void Bureaucrat::decrementGrade() {
	if (this->_grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade++;
}

// ex01 수정: 매개변수로 AForm을 받도록 변경
void Bureaucrat::signForm(AForm& form) {
	try {
		form.beSigned(*this);
		std::cout << this->_name << " signed " << form.getName() << std::endl;
	} catch (const std::exception& e) {
		std::cout << this->_name << " couldn't sign " << form.getName()
		          << " because " << e.what() << std::endl;
	}
}

// ex02 추가: 서류(Form)가 객체의 execute 메서드를 실행하도록 위임하는 역할
void Bureaucrat::executeForm(AForm const & form) {
	try {
		// 다형성을 이용해 서류의 구체적인 자식 객체의 execute를 호출합니다.
		form.execute(*this);
		std::cout << this->_name << " executed " << form.getName() << std::endl;
	} catch (const std::exception& e) {
		// 예외(권한 부족, 서명 안 됨 등)가 발생하면 실행 실패 이유를 출력합니다.
		std::cout << this->_name << " couldn't execute " << form.getName()
		          << " because " << e.what() << std::endl;
	}
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return "Bureaucrat grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
	return "Bureaucrat grade is too low!";
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat) {
	os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
	return os;
}