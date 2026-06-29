#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception>

// ex01의 Form 대신 추상 클래스인 AForm을 전방 선언
class AForm;

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

	// ex02 추가 및 변경: AForm 참조를 받도록 변경, 폼 실행 함수 추가
	void signForm(AForm& form);
	void executeForm(AForm const & form); // 폼의 다형성 실행을 위한 함수

	class GradeTooHighException : public std::exception {
	public: virtual const char* what() const throw(); };
	class GradeTooLowException : public std::exception {
	public: virtual const char* what() const throw(); };
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);

#endif