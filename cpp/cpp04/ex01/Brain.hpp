#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <string>

// ────────────────────────────────────────────────────────────
// Brain 클래스: Dog와 Cat이 동적으로 소유하는 "뇌" 객체
// 100개의 아이디어(ideas)를 배열로 관리
// ────────────────────────────────────────────────────────────
class Brain
{
	private:
		std::string ideas[100]; // 100개의 아이디어 문자열 배열

	public:
		Brain();                              // 기본 생성자
		Brain(const Brain &other);           // 복사 생성자 (깊은 복사)
		Brain &operator=(const Brain &other); // 대입 연산자 (깊은 복사)
		~Brain();                            // 소멸자

		// ── 아이디어 접근 함수 ──
		void setIdea(int index, const std::string &idea); // 아이디어 설정
		std::string getIdea(int index) const;                    // 아이디어 읽기
};

#endif
