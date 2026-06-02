#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception>

// Form 참조를 위한 전방 선언
class Form;

class Bureaucrat {
private:
	const std::string _name;
	int _grade;

public:
	Bureaucrat();
	Bureaucrat(const std::string& name, int grade);
	Bureaucrat(const Bureaucrat& other);
	Bureaucrat& operator=(const Bureaucrat& other);
	~Bureaucrat();

	const std::string& getName() const;
	int getGrade() const;

	void incrementGrade();
	void decrementGrade();

	// ex01에 추가된 함수: 지정된 Form 객체에 서명을 시도합니다.
	// 결과에 따라 성공 및 실패 메시지를 출력합니다.
	void signForm(Form& form);

	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

// 전역 출력 연산자
std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);

#endif
