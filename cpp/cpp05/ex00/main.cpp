#include "Bureaucrat.hpp"

int main() {
	// 콘솔 출력을 구분하기 위한 구분선 및 테스트 안내
	std::cout << "============================================" << std::endl;
	std::cout << "       C++ Module 05 ex00: Bureaucrat       " << std::endl;
	std::cout << "============================================" << std::endl << std::endl;

	// Test 1: 정상적인 생성 및 출력, 등급 증감 테스트
	std::cout << "[Test 1] Normal creation and basic functionality test" << std::endl;
	try {
		// 이름: "John", 등급: 50인 Bureaucrat 객체 생성
		Bureaucrat john("John", 50);
		std::cout << "Successfully created: " << john << std::endl;

		// 등급을 올려봅니다 (50 -> 49)
		std::cout << "Incrementing John's grade (incrementGrade)..." << std::endl;
		john.incrementGrade();
		std::cout << "Current state: " << john << std::endl;

		// 등급을 내려봅니다 (49 -> 50)
		std::cout << "Decrementing John's grade (decrementGrade)..." << std::endl;
		john.decrementGrade();
		std::cout << "Current state: " << john << std::endl;
	} catch (const std::exception& e) {
		// 예외가 발생하면 예외 메시지를 출력합니다.
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 2: 생성자 등급 초과(Too High) 예외 테스트
	std::cout << "[Test 2] Constructor grade too high (< 1) exception test" << std::endl;
	try {
		// 최고 등급인 1보다 높은 0으로 생성 시도
		std::cout << "Attempting to create Bureaucrat with grade 0..." << std::endl;
		Bureaucrat tom("Tom", 0);
		std::cout << "Successfully created: " << tom << std::endl;
	} catch (const std::exception& e) {
		// 1 미만이므로 GradeTooHighException 예외가 발생해야 합니다.
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 3: 생성자 등급 미달(Too Low) 예외 테스트
	std::cout << "[Test 3] Constructor grade too low (> 150) exception test" << std::endl;
	try {
		// 최저 등급인 150보다 낮은 151로 생성 시도
		std::cout << "Attempting to create Bureaucrat with grade 151..." << std::endl;
		Bureaucrat bob("Bob", 151);
		std::cout << "Successfully created: " << bob << std::endl;
	} catch (const std::exception& e) {
		// 150 초과이므로 GradeTooLowException 예외가 발생해야 합니다.
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 4: incrementGrade() 범위 초과 예외 테스트
	std::cout << "[Test 4] incrementGrade() grade too high exception test" << std::endl;
	try {
		// 최고 등급인 1인 Bureaucrat 객체 생성
		Bureaucrat boss("The Boss", 1);
		std::cout << "Created: " << boss << std::endl;

		// 등급 1에서 추가적으로 등급을 1 올리려 시도합니다 (0이 되려 함)
		std::cout << "Attempting to increment grade further..." << std::endl;
		boss.incrementGrade();
		std::cout << "Result: " << boss << std::endl;
	} catch (const std::exception& e) {
		// 1 미만이 되므로 예외가 던져져야 합니다.
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 5: decrementGrade() 범위 미달 예외 테스트
	std::cout << "[Test 5] decrementGrade() grade too low exception test" << std::endl;
	try {
		// 최저 등급인 150인 Bureaucrat 객체 생성
		Bureaucrat intern("Intern No.1", 150);
		std::cout << "Created: " << intern << std::endl;

		// 등급 150에서 추가적으로 등급을 1 내리려 시도합니다 (151이 되려 함)
		std::cout << "Attempting to decrement grade further..." << std::endl;
		intern.decrementGrade();
		std::cout << "Result: " << intern << std::endl;
	} catch (const std::exception& e) {
		// 150 초과가 되므로 예외가 던져져야 합니다.
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 6: Orthodox Canonical Form (복사 및 대입) 테스트
	std::cout << "[Test 6] Orthodox Canonical Form (Copy/Assignment) test" << std::endl;
	try {
		Bureaucrat origin("Origin", 42);
		std::cout << "Original object created: " << origin << std::endl;

		// 복사 생성자 테스트
		Bureaucrat copyConstructed(origin);
		std::cout << "Copy constructed object: " << copyConstructed << std::endl;

		// 대입 연산자 테스트
		Bureaucrat assigned("Temp", 100);
		std::cout << "Before assignment: " << assigned << std::endl;
		assigned = origin;
		std::cout << "After assignment: " << assigned << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << std::endl << "============================================" << std::endl;
	std::cout << "             All tests completed            " << std::endl;
	std::cout << "============================================" << std::endl;

	return 0;
}