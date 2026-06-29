#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("Default Form"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw AForm::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw AForm::GradeTooLowException();
}

AForm::AForm(const AForm& other)
	: _name(other._name), _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
}

AForm& AForm::operator=(const AForm& other) {
	if (this != &other) {
		this->_isSigned = other._isSigned;
	}
	return *this;
}

AForm::~AForm() {
}

const std::string& AForm::getName() const { return this->_name; }
bool AForm::getIsSigned() const { return this->_isSigned; }
int AForm::getGradeToSign() const { return this->_gradeToSign; }
int AForm::getGradeToExecute() const { return this->_gradeToExecute; }

void AForm::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > this->_gradeToSign)
		throw AForm::GradeTooLowException();
	this->_isSigned = true;
}

void AForm::verifyExecution(const Bureaucrat& executor) const {
	if (!this->_isSigned)
		throw AForm::NotSignedException();
	if (executor.getGrade() > this->_gradeToExecute)
		throw AForm::GradeTooLowException();
}

const char* AForm::GradeTooHighException::what() const throw() {
	return "Form grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw() {
	return "Form grade is too low!";
}

const char* AForm::NotSignedException::what() const throw() {
	return "Form is not signed!";
}

std::ostream& operator<<(std::ostream& os, const AForm& form) {
	os << form.getName() << " [Sign: " << form.getGradeToSign()
	   << ", Execute: " << form.getGradeToExecute()
	   << ", Signed: " << (form.getIsSigned() ? "Yes" : "No") << "]";
	return os;
}