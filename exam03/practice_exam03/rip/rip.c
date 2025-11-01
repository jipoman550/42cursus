/*
 * 주어진 괄호 문자열이 유효한지(균형이 맞는지) 확인하는 함수.
 * pset: 확인할 괄호 문자열
 * 반환값: 유효하면 1, 그렇지 않으면 0
 */
#include "rip.h"

int rip_is_valid(char *pset)
{
	int balance = 0; // 괄호의 균형을 추적하는 카운터

	// 문자열을 처음부터 끝까지 순회
	for (int i = 0; pset[i]; i++)
	{
		if (pset[i] == '(')
			balance++; // 여는 괄호를 만나면 카운터 증가
		else if (pset[i] == ')')
			balance--; // 닫는 괄호를 만나면 카운터 감소

		// 만약 카운터가 0보다 작아지면, 닫는 괄호가 여는 괄호보다 먼저 나온 것이므로 유효하지 않음
		if (balance < 0)
			return (0);
	}
	// 문자열 순회가 끝난 후, 카운터가 0이면 모든 괄호의 짝이 맞으므로 유효함
	return (balance == 0);
}

/*
 * 문자열을 균형잡힌 상태로 만들기 위해 제거해야 할 최소한의
 * 왼쪽 및 오른쪽 괄호의 수를 계산하는 함수.
 * s: 입력 괄호 문자열
 * l_rem: 제거해야 할 왼쪽 괄호의 수를 저장할 포인터
 * r_rem: 제거해야 할 오른쪽 괄호의 수를 저장할 포인터
 */
void get_min_removals(char *s, int *l_rem, int *r_rem)
{
	int balance = 0;
	*l_rem = 0;
	*r_rem = 0;

	// 문자열을 순회하며 제거할 괄호 수 계산
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == '(')
		{
			balance++; // 여는 괄호는 카운터 증가
		}
		else if (s[i] == ')')
		{
			// 짝 맞는 여는 괄호가 있으면 카운터 감소
			if (balance > 0)
				balance--;
			// 짝 맞는 여는 괄호가 없으면, 이 닫는 괄호는 제거 대상임
			else
				(*r_rem)++;
		}
	}
	// 순회가 끝난 후 남은 카운터는 제거해야 할 여는 괄호 '(' 의 수와 같음
	*l_rem = balance;
}

/*
 * 재귀적으로 모든 유효한 괄호 조합을 찾고 출력하는 함수 (깊이 우선 탐색 - DFS)
 * pset: 현재 처리 중인 괄호 문자열 (수정될 수 있음)
 * start_index: 탐색을 시작할 인덱스 (중복 탐색 방지)
 * l_rem: 제거해야 할 남은 왼쪽 괄호의 수 '('
 * r_rem: 제거해야 할 남은 오른쪽 괄호의 수 ')'
 */
void rip_recursive(
	char *pset,
	int start_index,
	int l_rem,
	int r_rem
)
{
	// 재귀 종료 조건: 제거해야 할 괄호가 더 이상 없으면
	if (l_rem == 0 && r_rem == 0)
	{
		// 현재 문자열이 유효한 괄호 조합인지 확인
		if (rip_is_valid(pset))
			puts(pset); // 유효하다면 결과 출력
		return;
	}

	// DFS 탐색: start_index부터 문자열 끝까지 순회하며 제거할 괄호를 찾음
	for (int i = start_index; pset[i]; i++)
	{
		// 현재 문자가 괄호가 아니면 건너뜀
		if (pset[i] != '(' && pset[i] != ')')
			continue;

		// 왼쪽 괄호 제거 경로 탐색
		if (pset[i] == '(' && l_rem > 0)
		{
			pset[i] = ' '; // 괄호를 공백으로 변경하여 "제거"
			// 현재 위치(i) 다음부터, 제거할 왼쪽 괄호 수를 하나 줄여서 재귀 호출
			rip_recursive(pset, i + 1, l_rem - 1, r_rem);
			pset[i] = '('; // 백트래킹: 다음 탐색을 위해 원래 문자로 복원
		}

		// 오른쪽 괄호 제거 경로 탐색
		if (pset[i] == ')' && r_rem > 0)
		{
			pset[i] = ' '; // 괄호를 공백으로 변경하여 "제거"
			// 현재 위치(i) 다음부터, 제거할 오른쪽 괄호 수를 하나 줄여서 재귀 호출
			rip_recursive(pset, i + 1, l_rem, r_rem - 1);
			pset[i] = ')'; // 백트래킹: 다음 탐색을 위해 원래 문자로 복원
		}
	}
}

/*
 * 프로그램의 메인 함수
 */
int main(int ac, char **av)
{
	// 인자가 1개가 아니면 프로그램 종료
	if (ac != 2 || !av[1])
		return (0);

	int l_rem = 0; // 제거할 왼쪽 괄호 수 '('
	int r_rem = 0; // 제거할 오른쪽 괄호 수 ')'

	// 제거해야 할 최소 괄호 수 계산
	get_min_removals(av[1], &l_rem, &r_rem);
	// 재귀 함수를 호출하여 모든 가능한 유효한 문자열을 찾아 출력
	rip_recursive(av[1], 0, l_rem, r_rem);

	return (0);
}
