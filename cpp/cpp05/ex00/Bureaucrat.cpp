#include "Bureaucrat.hpp"

// 기본 생성자
// 기본값으로 이름은 "Default", 등급은 최저 등급인 150으로 설정합니다.
Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) {
	// 기본 생성자에서도 예외 처리를 위해 범위 검사를 진행할 수 있으나,
	// 150은 유효한 등급이므로 안전합니다.
}

// 매개변수 생성자
// 이름과 등급을 받아 초기화하며, 등급이 유효한 범위(1~150)인지 검사합니다.
Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
	// 등급이 1보다 작으면 GradeTooHighException 예외를 던집니다.
	if (grade < 1) {
		throw Bureaucrat::GradeTooHighException();
	}
	// 등급이 150보다 크면 GradeTooLowException 예외를 던집니다.
	if (grade > 150) {
		throw Bureaucrat::GradeTooLowException();
	}
	// 유효한 등급인 경우 멤버 변수에 저장합니다.
	this->_grade = grade;
}

// 복사 생성자
// 다른 Bureaucrat 객체의 이름과 등급을 복사하여 객체를 생성합니다.
Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade) {
	// 이미 존재하는 객체를 복사하므로 등급 검사는 생략할 수 있습니다.
}

// 복사 대입 연산자 오버로딩
// _name은 const std::string이므로 대입이 불가합니다.
// 따라서 등급(_grade) 정보만 복사하여 할당합니다.
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
	// 자기 자신을 대입하는 경우인지 확인합니다.
	if (this != &other) {
		this->_grade = other._grade;
	}
	// 대입된 객체의 참조를 반환합니다.
	return *this;
}

// 소멸자
// 객체가 메모리에서 해제될 때 호출됩니다.
Bureaucrat::~Bureaucrat() {
}

// getName 접근자
// const 참조로 Bureaucrat의 이름을 반환합니다.
const std::string& Bureaucrat::getName() const {
	return this->_name;
}

// getGrade 접근자
// Bureaucrat의 등급을 정수형으로 반환합니다.
int Bureaucrat::getGrade() const {
	return this->_grade;
}

// incrementGrade(): 등급을 1 증가시킵니다.
// 관료 사회에서 숫자가 작을수록 높은 등급이므로 등급 수치(_grade)를 감소시킵니다.
void Bureaucrat::incrementGrade() {
	// 변경 후 등급이 1보다 작아질 경우 GradeTooHighException 예외를 던집니다.
	if (this->_grade - 1 < 1) {
		throw Bureaucrat::GradeTooHighException();
	}
	// 등급이 안전한 범위인 경우 값을 수정합니다.
	this->_grade--;
}

// decrementGrade(): 등급을 1 감소시킵니다.
// 관료 사회에서 숫자가 클수록 낮은 등급이므로 등급 수치(_grade)를 증가시킵니다.
void Bureaucrat::decrementGrade() {
	// 변경 후 등급이 150보다 커질 경우 GradeTooLowException 예외를 던집니다.
	if (this->_grade + 1 > 150) {
		throw Bureaucrat::GradeTooLowException();
	}
	// 등급이 안전한 범위인 경우 값을 수정합니다.
	this->_grade++;
}

// GradeTooHighException::what() 오버라이딩
// 등급이 너무 높을 때 발생할 예외 메시지를 문자열로 반환합니다.
const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return "Bureaucrat grade is too high! (Must be between 1 and 150)";
}

// GradeTooLowException::what() 오버라이딩
// 등급이 너무 낮을 때 발생할 예외 메시지를 문자열로 반환합니다.
const char* Bureaucrat::GradeTooLowException::what() const throw() {
	return "Bureaucrat grade is too low! (Must be between 1 and 150)";
}

// 전역 삽입 연산자(<<) 오버로딩
// 출력 형식: <name>, bureaucrat grade <grade>.
std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat) {
	os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
	return os;
}
