#include "RPN.hpp"
#include <sstream>
#include <cctype>
#include <iostream>

// --- Orthodox Canonical Class Form ---

/**
 * @brief RPN 클래스의 기본 생성자.
 */
RPN::RPN() {}

/**
 * @brief RPN 클래스의 복사 생성자.
 * @param src 복사할 원본 RPN 객체.
 */
RPN::RPN(const RPN& src)
{
	*this = src;
}

/**
 * @brief RPN 클래스의 복사 대입 연산자.
 * @param rhs 대입할 우변 RPN 객체.
 * @return 갱신된 현재 객체의 참조.
 */
RPN& RPN::operator=(const RPN& rhs)
{
	if (this != &rhs)
	{
		this->_stack = rhs._stack;
	}
	return (*this);
}

/**
 * @brief RPN 클래스의 소멸자.
 */
RPN::~RPN() {}

// --- Public Methods ---

/**
 * @brief RPN 수식을 파싱하고 계산합니다.
 * @param expression 공백으로 구분된 RPN 수식 문자열.
 * @throw RPNException 수식이 유효하지 않거나 계산 중 오류가 발생할 경우.
 */
void RPN::calculate(const std::string& expression)
{
	// 문자열 스트림을 사용하여 공백을 기준으로 토큰을 분리합니다.
	std::stringstream ss(expression);
	std::string token;

	// 스트림에서 토큰을 하나씩 읽어옵니다.
	while (ss >> token)
	{
		// 토큰이 연산자인 경우 (+, -, *, /)
		if (token.length() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'))
		{
			// 스택에 피연산자가 2개 미만이면 연산이 불가능하므로 에러 처리합니다.
			if (_stack.size() < 2)
			{
				throw RPNException();
			}
			// 연산을 수행하는 헬퍼 함수를 호출합니다.
			executeOperation(token[0]);
		}
		// 토큰이 한 자리 숫자인 경우 (0-9)
		else if (token.length() == 1 && std::isdigit(token[0]))
		{
			// 토큰을 정수로 변환하여 스택에 푸시합니다. ('0'의 아스키 값을 빼서 실제 숫자 값으로 변환)
			_stack.push(token[0] - '0');
		}
		// 토큰이 유효하지 않은 경우 (길이가 1을 초과하거나, 숫자가 아니거나, 지원하지 않는 문자)
		else
		{
			throw RPNException();
		}
	}

	// 모든 토큰 처리가 끝난 후, 스택에 결과값 하나만 남아있어야 합니다.
	// 1개가 아니면(많거나 부족하면) 수식이 잘못된 것이므로 에러 처리합니다.
	if (_stack.size() != 1)
	{
		throw RPNException();
	}

	// 최종 결과값을 표준 출력에 출력합니다.
	std::cout << _stack.top() << std::endl;
}

// --- Private Helper Methods ---

/**
 * @brief 스택에서 두 피연산자를 꺼내 사칙연산을 수행하고 결과를 다시 스택에 넣습니다.
 * @param op 수행할 연산자 (+, -, *, /).
 * @throw RPNException 0으로 나누기를 시도할 경우.
 */
void RPN::executeOperation(char op)
{
	// 스택의 맨 위(가장 나중에 들어온) 숫자가 우항(RHS)이 됩니다.
	int rhs = _stack.top();
	_stack.pop();
	// 그 다음 숫자가 좌항(LHS)이 됩니다.
	int lhs = _stack.top();
	_stack.pop();

	// 연산자 종류에 따라 분기하여 계산하고 결과를 다시 스택에 푸시합니다.
	if (op == '+')
	{
		_stack.push(lhs + rhs);
	}
	else if (op == '-')
	{
		_stack.push(lhs - rhs);
	}
	else if (op == '*')
	{
		_stack.push(lhs * rhs);
	}
	else if (op == '/')
	{
		// 0으로 나누기(division by zero) 오류를 방지합니다.
		if (rhs == 0)
		{
			throw RPNException();
		}
		_stack.push(lhs / rhs);
	}
}

// --- Custom Exception ---

const char* RPN::RPNException::what() const throw()
{
	return ("Error");
}