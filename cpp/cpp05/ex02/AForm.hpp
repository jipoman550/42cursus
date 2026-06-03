#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include <string>
# include <exception>

class Bureaucrat;

// 추상 클래스(Abstract Class) 선언을 위한 AForm 클래스
// 'A' 접두사는 Abstract를 의미하며, 이 클래스는 직접 인스턴스화할 수 없습니다.
class AForm {
private:
	const std::string _name;
	bool _isSigned;
	const int _gradeToSign;
	const int _gradeToExecute;

public:
	// Orthodox Canonical Form
	AForm();
	AForm(const std::string& name, int gradeToSign, int gradeToExecute);
	AForm(const AForm& other);
	AForm& operator=(const AForm& other);
	virtual ~AForm(); // 다형성을 위해 가상 소멸자 필수

	// Getters
	const std::string& getName() const;
	bool getIsSigned() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;

	// 서명 로직 (ex01과 동일)
	void beSigned(const Bureaucrat& bureaucrat);

	// 실행 가능 여부를 검증하는 공통 로직
	// 서류가 서명되지 않았거나, 관료의 등급이 부족할 때 예외를 던집니다.
	void verifyExecution(const Bureaucrat& executor) const;

	// 순수 가상 함수 (Pure Virtual Function)
	// 이 함수가 존재함으로서 AForm은 추상 클래스가 되며,
	// 모든 파생 클래스는 이 함수를 반드시 구현해야 합니다.
	virtual void execute(Bureaucrat const & executor) const = 0;

	// 기존 예외 클래스
	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	// 서명되지 않은 서류를 실행하려 할 때 발생시킬 예외
	class NotSignedException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif