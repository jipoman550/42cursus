#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>
# include <exception>

// 순환 참조를 방지하기 위해 전방 선언을 사용합니다.
class Bureaucrat;

class Form {
private:
	// 서류의 이름 (상수로 한 번 정해지면 변경 불가)
	const std::string _name;
	// 서류의 서명 여부 상태 (기본값: false)
	bool _isSigned;
	// 서류에 서명하기 위해 필요한 최소 요구 등급 (상수)
	const int _gradeToSign;
	// 서류를 실행하기 위해 필요한 최소 요구 등급 (상수)
	const int _gradeToExecute;

public:
	// Orthodox Canonical Form
	// 1. 기본 생성자
	Form();
	// 매개변수 생성자 (이름, 서명 요구 등급, 실행 요구 등급 초기화)
	Form(const std::string& name, int gradeToSign, int gradeToExecute);
	// 2. 복사 생성자
	Form(const Form& other);
	// 3. 복사 대입 연산자 오버로딩
	Form& operator=(const Form& other);
	// 4. 소멸자
	~Form();

	// 모든 속성에 대한 접근자(Getters)
	const std::string& getName() const;
	bool getIsSigned() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;

	// 관료(Bureaucrat)의 정보를 받아 서류에 서명하는 기능
	// 관료의 등급이 서명 요구 등급보다 낮을 경우 예외를 발생시킵니다.
	void beSigned(const Bureaucrat& bureaucrat);

	// 예외 처리 클래스 정의 (std::exception 상속)
	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

// 삽입 연산자(<<) 오버로딩 (전역 함수)
// Form 객체의 모든 속성을 한 번에 출력할 수 있도록 정의합니다.
std::ostream& operator<<(std::ostream& os, const Form& form);

#endif
