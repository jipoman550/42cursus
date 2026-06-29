#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception>

class Bureaucrat {
private:
	// const std::string name: 이름은 한 번 정해지면 변경할 수 없습니다.
	const std::string _name;
	// int grade: 등급은 1(최고)에서 150(최저) 사이여야 합니다.
	int _grade;

public:
	// Orthodox Canonical Form (정통 캐노니컬 형식)
	// 1. 기본 생성자: 기본값으로 이름 "Default", 등급 150(최저)을 부여합니다.
	Bureaucrat();
	// 매개변수 생성자: 이름과 등급을 받아 객체를 생성합니다.
	Bureaucrat(const std::string& name, int grade);
	// 2. 복사 생성자: 다른 Bureaucrat 객체의 정보를 복사하여 생성합니다.
	Bureaucrat(const Bureaucrat& other);
	// 3. 대입 연산자 오버로딩: 다른 객체의 등급 정보를 대입합니다. (_name은 const이므로 대입 불가, _grade만 대입)
	Bureaucrat& operator=(const Bureaucrat& other);
	// 4. 소멸자: 객체 소멸 시 호출됩니다.
	~Bureaucrat();

	// 접근자(Getters)
	// getName(): 객체의 이름을 반환합니다.
	const std::string& getName() const;
	// getGrade(): 객체의 등급을 반환합니다.
	int getGrade() const;

	// 등급 조절 함수
	// incrementGrade(): 등급을 1 올립니다. (관료제이므로 grade 수치는 1 감소합니다)
	void incrementGrade();
	// decrementGrade(): 등급을 1 내립니다. (관료제이므로 grade 수치는 1 증가합니다)
	void decrementGrade();

	// 내부 클래스로 예외 정의 (std::exception 상속)
	// GradeTooHighException: 등급이 1 미만으로 높아지려고 할 때 던질 예외
	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	// GradeTooLowException: 등급이 150 초과로 낮아지려고 할 때 던질 예외
	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

// 3. 연산자 오버로딩 (전역 함수)
// 삽입 연산자 (<<): Bureaucrat 객체의 정보를 출력 스트림으로 전달합니다.
// 출력 형식: <name>, bureaucrat grade <grade>.
std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);

#endif
