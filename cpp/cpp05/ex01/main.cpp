#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
	std::cout << "=================================================" << std::endl;
	std::cout << "         C++ Module 05 ex01: Form Test           " << std::endl;
	std::cout << "=================================================" << std::endl << std::endl;

	// [Test 1] Form 객체 생성 중 범위 오류 시 예외 테스트
	std::cout << "[Test 1] Form Construction Exception Test" << std::endl;
	try {
		// 서명 권한을 최고 등급인 1보다 높은 0으로 시도 (에러 발생 예상)
		std::cout << "Attempting to create a Form with Sign Grade 0..." << std::endl;
		Form invalidForm("TopSecret", 0, 50);
		std::cout << invalidForm << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// [Test 2] 등급이 높은 관료의 서명 성공 케이스
	std::cout << "[Test 2] Successful Form Signing Test" << std::endl;
	try {
		Bureaucrat boss("Boss", 10); // 관료의 등급은 10
		Form importantDoc("Important Document", 20, 50); // 서명을 위한 요구 등급은 20

		std::cout << boss << std::endl;
		std::cout << importantDoc << std::endl;

		// 10(관료) <= 20(서류) 이므로 서명이 성공해야 함
		boss.signForm(importantDoc);

		// 서명 성공 이후의 객체 상태 출력 (Status가 Signed로 바뀌어 있어야 함)
		std::cout << std::endl << "After signing attempt:" << std::endl;
		std::cout << importantDoc << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// [Test 3] 등급이 낮은 관료의 서명 실패 케이스
	std::cout << "[Test 3] Failed Form Signing Test (Grade Too Low)" << std::endl;
	try {
		Bureaucrat intern("Intern", 150); // 최하급 관료
		Form regularDoc("Regular Document", 100, 100); // 요구 등급 100

		std::cout << intern << std::endl;
		std::cout << regularDoc << std::endl;

		// 150(관료) > 100(서류) 이므로 서명에 실패하고, catch 블록에서 에러 메시지를 출력함
		intern.signForm(regularDoc);
	} catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	return 0;
}
