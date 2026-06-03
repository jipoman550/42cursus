#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

// 부모(AForm)의 생성자를 호출하여 이름과 요구 등급(Sign:145, Exec:137)을 설정합니다.
ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("ShrubberyCreationForm", 145, 137), _target("default_target") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), _target(other._target) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
	if (this != &other) {
		AForm::operator=(other); // 부모 클래스의 대입 연산자 호출
		this->_target = other._target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

// 실제 폼의 기능(Action) 실행
void ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
	// 1. 공통 검증 로직 호출 (권한이 없거나 서명이 안 되어 있으면 여기서 throw 됨)
	this->verifyExecution(executor);

	// 2. 파일 스트림 열기 및 ASCII Tree 그리기
	std::string filename = this->_target + "_shrubbery";
	std::ofstream ofs(filename.c_str());

	if (!ofs.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}
	// ASCII 나무 디자인 출력
	ofs << "      /\\      \n     /\\*\\     \n    /\\O\\*\\    \n   /*/\\/\\/\\   \n  /\\O\\/\\*\\/\\  \n /\\*\\/\\*\\/\\/\\ \n/\\O\\/\\/*/\\/O/\\\n      ||      \n      ||      \n      ||      \n";
	ofs.close();
	std::cout << "Shrubbery created successfully at " << filename << std::endl;
}