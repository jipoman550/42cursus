#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>
# include <string>

// Harl 클래스는 다양한 수준의 불평을 시뮬레이션합니다.
class Harl {
	private:
		// "DEBUG" 수준의 메시지를 출력하는 private 멤버 함수입니다.
		void debug(void);
		// "INFO" 수준의 메시지를 출력하는 private 멤버 함수입니다.
		void info(void);
		// "WARNING" 수준의 메시지를 출력하는 private 멤버 함수입니다.
		void warning(void);
		// "ERROR" 수준의 메시지를 출력하는 private 멤버 함수입니다.
		void error(void);

	public:
		// Harl 객체를 생성하는 생성자입니다.
		Harl();
		// Harl 객체를 소멸시키는 소멸자입니다.
		~Harl();
		// 주어진 수준(level)에 해당하는 불평 메시지를 호출합니다.
		void complain(std::string level);
};

#endif
