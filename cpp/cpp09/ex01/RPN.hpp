#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>
# include <stdexcept>

/**
 * @class RPN
 * @brief 역폴란드 표기법(RPN) 수식을 계산하는 클래스.
 * @details std::stack을 사용하여 RPN 수식을 파싱하고 계산하는 기능을 제공합니다.
 *          입력 수식은 공백으로 구분된 토큰으로 구성되어야 하며,
 *          피연산자는 0-9 사이의 한 자리 숫자여야 합니다.
 */
class RPN {
private:
	std::stack<int> _stack;

	// Private helper methods
	void executeOperation(char op);

public:
	// --- Orthodox Canonical Class Form ---
	RPN();
	RPN(const RPN& src);
	RPN& operator=(const RPN& rhs);
	~RPN();

	// --- Public Methods ---
	void calculate(const std::string& expression);

	// --- Custom Exception ---
	class RPNException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

#endif
