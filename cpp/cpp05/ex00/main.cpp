#include "Bureaucrat.hpp"

int main() {
	// 콘솔 출력을 구분하기 위한 구분선 및 테스트 안내
	std::cout << "============================================" << std::endl;
	std::cout << "       C++ Module 05 ex00: Bureaucrat       " << std::endl;
	std::cout << "============================================" << std::endl << std::endl;

	// Test 1: 정상적인 생성 및 출력, 등급 증감 테스트
	std::cout << "[Test 1] 정상 생성 및 기본 기능 테스트" << std::endl;
	try {
		// 이름: "John", 등급: 50인 Bureaucrat 객체 생성
		Bureaucrat john("John", 50);
		std::cout << "성공적으로 생성됨: " << john << std::endl;

		// 등급을 올려봅니다 (50 -> 49)
		std::cout << "John의 등급을 1 올립니다 (incrementGrade)..." << std::endl;
		john.incrementGrade();
		std::cout << "현재 상태: " << john << std::endl;

		// 등급을 내려봅니다 (49 -> 50)
		std::cout << "John의 등급을 1 내립니다 (decrementGrade)..." << std::endl;
		john.decrementGrade();
		std::cout << "현재 상태: " << john << std::endl;
	} catch (const std::exception& e) {
		// 예외가 발생하면 예외 메시지를 출력합니다.
		std::cerr << "예외 발생: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 2: 생성자 등급 초과(Too High) 예외 테스트
	std::cout << "[Test 2] 생성자 등급 너무 높음 (< 1) 예외 테스트" << std::endl;
	try {
		// 최고 등급인 1보다 높은 0으로 생성 시도
		std::cout << "등급 0으로 Bureaucrat 생성 시도..." << std::endl;
		Bureaucrat tom("Tom", 0);
		std::cout << "성공적으로 생성됨: " << tom << std::endl;
	} catch (const std::exception& e) {
		// 1 미만이므로 GradeTooHighException 예외가 발생해야 합니다.
		std::cerr << "예외 잡힘: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 3: 생성자 등급 미달(Too Low) 예외 테스트
	std::cout << "[Test 3] 생성자 등급 너무 낮음 (> 150) 예외 테스트" << std::endl;
	try {
		// 최저 등급인 150보다 낮은 151로 생성 시도
		std::cout << "등급 151로 Bureaucrat 생성 시도..." << std::endl;
		Bureaucrat bob("Bob", 151);
		std::cout << "성공적으로 생성됨: " << bob << std::endl;
	} catch (const std::exception& e) {
		// 150 초과이므로 GradeTooLowException 예외가 발생해야 합니다.
		std::cerr << "예외 잡힘: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 4: incrementGrade() 범위 초과 예외 테스트
	std::cout << "[Test 4] incrementGrade() 등급 초과 예외 테스트" << std::endl;
	try {
		// 최고 등급인 1인 Bureaucrat 객체 생성
		Bureaucrat supreme("Supreme Boss", 1);
		std::cout << "생성됨: " << supreme << std::endl;

		// 등급 1에서 추가적으로 등급을 1 올리려 시도합니다 (0이 되려 함)
		std::cout << "Supreme Boss의 등급을 더 올립니다..." << std::endl;
		supreme.incrementGrade();
		std::cout << "결과: " << supreme << std::endl;
	} catch (const std::exception& e) {
		// 1 미만이 되므로 예외가 던져져야 합니다.
		std::cerr << "예외 잡힘: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 5: decrementGrade() 범위 미달 예외 테스트
	std::cout << "[Test 5] decrementGrade() 등급 미달 예외 테스트" << std::endl;
	try {
		// 최저 등급인 150인 Bureaucrat 객체 생성
		Bureaucrat intern("Intern No.1", 150);
		std::cout << "생성됨: " << intern << std::endl;

		// 등급 150에서 추가적으로 등급을 1 내리려 시도합니다 (151이 되려 함)
		std::cout << "Intern No.1의 등급을 더 내립니다..." << std::endl;
		intern.decrementGrade();
		std::cout << "결과: " << intern << std::endl;
	} catch (const std::exception& e) {
		// 150 초과가 되므로 예외가 던져져야 합니다.
		std::cerr << "예외 잡힘: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 6: Orthodox Canonical Form (복사 및 대입) 테스트
	std::cout << "[Test 6] Orthodox Canonical Form (복사/대입) 테스트" << std::endl;
	try {
		Bureaucrat origin("Origin", 42);
		std::cout << "원본 객체 생성: " << origin << std::endl;

		// 복사 생성자 테스트
		Bureaucrat copyConstructed(origin);
		std::cout << "복사 생성된 객체: " << copyConstructed << std::endl;

		// 기본 생성 후 대입 연산자 테스트
		Bureaucrat assigned;
		std::cout << "대입 전 기본 객체: " << assigned << std::endl;
		assigned = origin;
		std::cout << "대입 후 객체(이름은 const이므로 유지, 등급만 대입되어야 함): " << assigned << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "예외 발생: " << e.what() << std::endl;
	}

	std::cout << std::endl << "============================================" << std::endl;
	std::cout << "             테스트가 완료되었습니다.       " << std::endl;
	std::cout << "============================================" << std::endl;

	return 0;
}
