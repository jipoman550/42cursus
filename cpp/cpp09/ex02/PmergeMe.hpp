#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <string>
# include <stdexcept>
# include <sys/time.h>
# include <utility>

/**
 * @class PmergeMe
 * @brief Ford-Johnson(Merge-Insert Sort) 알고리즘을 사용하여 컨테이너를 정렬하는 유틸리티 클래스.
 * @details 이 클래스는 std::vector와 std::deque에 대해 각각 최적화된 정렬 메서드를 제공합니다.
 *          인스턴스화할 수 없으며 모든 멤버 함수는 static으로 호출됩니다.
 */
class PmergeMe {
private:
	// Orthodox Canonical Class Form (private)
	// 이 클래스는 유틸리티성 정적 멤버 함수만 제공하므로 인스턴스화를 방지합니다.
	PmergeMe();
	PmergeMe(const PmergeMe& src);
	PmergeMe& operator=(const PmergeMe& rhs);
	~PmergeMe();

	// --- Vector specific Ford-Johnson implementation ---
	/**
	 * @brief std::vector에 대해 Ford-Johnson 알고리즘을 수행합니다.
	 * @param vec 정렬할 정수 벡터.
	 */
	static void fordJohnsonSort(std::vector<int>& vec);
	/**
	 * @brief Jacobsthal 수열을 생성합니다. (vector 버전)
	 * @param jacob 수열을 저장할 벡터.
	 * @param n 수열에 포함될 원소의 최대 개수.
	 */
	static void generateJacobsthal(std::vector<int>& jacob, int n);

	// --- Deque specific Ford-Johnson implementation ---
	/**
	 * @brief std::deque에 대해 Ford-Johnson 알고리즘을 수행합니다.
	 * @param deq 정렬할 정수 덱.
	 */
	static void fordJohnsonSort(std::deque<int>& deq);
	/**
	 * @brief Jacobsthal 수열을 생성합니다. (deque 버전)
	 * @param jacob 수열을 저장할 덱.
	 * @param n 수열에 포함될 원소의 최대 개수.
	 */
	static void generateJacobsthal(std::deque<int>& jacob, int n);

public:
	// --- Main execution function ---
	/**
	 * @brief 프로그램의 전체 프로세스를 관리하는 메인 실행 함수.
	 * @details 인자 파싱, 시간 측정, 정렬 실행, 결과 출력을 총괄합니다.
	 * @param argc 커맨드 라인 인자의 개수.
	 * @param argv 커맨드 라인 인자 배열.
	 */
	static void process(int argc, char **argv);

	// --- Custom Exception ---
	/**
	 * @class ErrorException
	 * @brief 파싱 오류 등 프로그램 실행 중 발생하는 에러를 위한 사용자 정의 예외 클래스.
	 */
	class ErrorException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

#endif
