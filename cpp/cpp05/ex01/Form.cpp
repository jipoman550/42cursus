#include "Form.hpp"
#include "Bureaucrat.hpp"

// 기본 생성자
// 기본값으로 모든 서명 및 실행 요구 등급을 150으로 설정합니다.
Form::Form() : _name("Default Form"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {
}

// 매개변수 생성자
// 지정된 등급이 1~150 범위를 벗어날 경우 Bureaucrat와 동일하게 예외를 던집니다.
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1) {
		throw Form::GradeTooHighException();
	}
	if (gradeToSign > 150 || gradeToExecute > 150) {
		throw Form::GradeTooLowException();
	}
}

// 복사 생성자
// 다른 Form 객체를 복사할 때 호출됩니다.
Form::Form(const Form& other)
	: _name(other._name), _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
}

// 복사 대입 연산자 오버로딩
// _name, _gradeToSign, _gradeToExecute는 상수(const)이므로 값을 변경할 수 없습니다.
// 따라서 대입이 가능한 유일한 상태인 _isSigned(서명 여부) 값만 복사합니다.
Form& Form::operator=(const Form& other) {
	if (this != &other) {
		this->_isSigned = other._isSigned;
	}
	return *this;
}

// 소멸자
Form::~Form() {
}

// 접근자(Getters) 구현부
const std::string& Form::getName() const { return this->_name; }
bool Form::getIsSigned() const { return this->_isSigned; }
int Form::getGradeToSign() const { return this->_gradeToSign; }
int Form::getGradeToExecute() const { return this->_gradeToExecute; }

// beSigned 함수: 서명 시도 로직
// 인자로 받은 Bureaucrat의 등급과 현재 서류의 서명 요구 등급을 비교합니다.
// Bureaucrat의 등급 숫자가 더 크다면(즉, 실제 권한이 낮다면) 예외를 발생시킵니다.
void Form::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > this->_gradeToSign) {
		throw Form::GradeTooLowException();
	}
	this->_isSigned = true; // 권한이 충분하다면 서명 완료 처리
}

// 예외 발생 시의 메시지를 반환합니다.
const char* Form::GradeTooHighException::what() const throw() {
	return "Form grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
	return "Form grade is too low!";
}

// 삽입 연산자(<<) 오버로딩 구현
// Form 클래스가 가진 모든 정보를 정돈된 형태로 출력합니다.
std::ostream& operator<<(std::ostream& os, const Form& form) {
	os << "------------------------------------------\n"
	   << " Form Details \n"
	   << "------------------------------------------\n"
	   << " Name                 : " << form.getName() << "\n"
	   << " Status               : ";
	if (form.getIsSigned())
		os << "Signed\n";
	else
		os << "Unsigned\n";
	os << " Required Sign Grade  : " << form.getGradeToSign() << "\n"
	   << " Required Exec Grade  : " << form.getGradeToExecute() << "\n"
	   << "------------------------------------------";
	return os;
}
