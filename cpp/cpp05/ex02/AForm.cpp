#include "AForm.hpp"
#include "Bureaucrat.hpp"

// 기본 생성자
AForm::AForm() : _name("Default Form"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {
}

// 매개변수 생성자 (등급 범위 체크 포함)
AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw AForm::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw AForm::GradeTooLowException();
}

// 복사 생성자
AForm::AForm(const AForm& other)
	: _name(other._name), _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
}

// 대입 연산자 (상수는 변경할 수 없으므로 서명 상태만 복사)
AForm& AForm::operator=(const AForm& other) {
	if (this != &other) {
		this->_isSigned = other._isSigned;
	}
	return *this;
}

// 가상 소멸자
AForm::~AForm() {
}

// Getters
const std::string& AForm::getName() const { return this->_name; }
bool AForm::getIsSigned() const { return this->_isSigned; }
int AForm::getGradeToSign() const { return this->_gradeToSign; }
int AForm::getGradeToExecute() const { return this->_gradeToExecute; }

// 서명 기능
void AForm::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > this->_gradeToSign)
		throw AForm::GradeTooLowException();
	this->_isSigned = true;
}

// 공통 실행 검증 기능 (모든 자식 클래스의 execute() 첫 줄에서 호출됨)
void AForm::verifyExecution(const Bureaucrat& executor) const {
	if (!this->_isSigned)
		throw AForm::NotSignedException(); // 서류가 서명되지 않았을 때
	if (executor.getGrade() > this->_gradeToExecute)
		throw AForm::GradeTooLowException(); // 실행할 권한이 부족할 때
}

// 예외 클래스들의 what() 오버라이딩
const char* AForm::GradeTooHighException::what() const throw() {
	return "Form grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw() {
	return "Form grade is too low!";
}

const char* AForm::NotSignedException::what() const throw() {
	return "Form is not signed!";
}

// 삽입 연산자 오버로딩
std::ostream& operator<<(std::ostream& os, const AForm& form) {
	os << form.getName() << " [Sign: " << form.getGradeToSign()
	   << ", Execute: " << form.getGradeToExecute()
	   << ", Signed: " << (form.getIsSigned() ? "Yes" : "No") << "]";
	return os;
}