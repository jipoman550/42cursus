#include "powerset.h" // printf, malloc, free, atoi 등이 선언된 헤더로 추정

/*
** 함수: print_solution
** 설명: 조건을 만족하는 부분집합(buffer)의 내용을 출력합니다.
** 매개변수: tab (출력할 배열), len (출력할 길이)
*/
void print_solution(int *tab, int len)
{
	int i = 0;
	while (i < len)
	{
		printf("%d", tab[i]);
		// 마지막 숫자가 아닐 경우에만 숫자 사이에 공백을 출력
		if (i < len - 1)
			printf(" ");
		i++;
	}
	printf("\n"); // 한 줄의 출력이 끝나면 개행
}

/*
** 함수: solve
** 설명: 재귀적으로 숫자를 포함하거나 포함하지 않는 모든 경우를 탐색합니다 (깊이 우선 탐색, DFS).
** 매개변수:
** - cnt: 입력된 전체 숫자의 개수
** - nums: 입력된 숫자들을 담고 있는 배열
** - target: 만들고자 하는 목표 합
** - idx: 현재 검토 중인 nums 배열의 인덱스
** - current_sum: 현재까지 선택된 숫자들의 합
** - buffer: 선택된 숫자들을 저장하는 임시 배열
** - buf_idx: buffer 배열에 저장된 숫자의 개수 (현재 인덱스)
*/
void solve(int cnt, int *nums, int target, int idx, int current_sum, int *buffer, int buf_idx)
{
	// [기저 조건] 모든 숫자에 대해 포함 여부를 결정했을 때 (배열 끝에 도달)
	if (idx == cnt)
	{
		// 현재까지의 합이 목표값(target)과 같다면 정답으로 출력
		if (current_sum == target)
			print_solution(buffer, buf_idx);
		return ;
	}

	// [분기 1] 현재 숫자(nums[idx])를 부분집합에 '포함하는' 경우
	buffer[buf_idx] = nums[idx]; // 버퍼에 현재 숫자 저장
	solve(cnt, nums, target, idx + 1, current_sum + nums[idx], buffer, buf_idx + 1);
	// 설명: 다음 인덱스(idx+1)로 이동하고, 합계에 현재 값을 더하며, 버퍼 인덱스도 증가시킴

	// [분기 2] 현재 숫자(nums[idx])를 부분집합에 '포함하지 않는' 경우
	solve(cnt, nums, target, idx + 1, current_sum, buffer, buf_idx);
	// 설명: 다음 인덱스(idx+1)로 이동하지만, 합계는 그대로 유지하고, 버퍼 인덱스도 증가시키지 않음
	// (버퍼의 해당 위치는 다음 재귀에서 다른 값으로 덮어씌워지거나 무시됨)
}

int main(int argc, char **argv)
{
	// 인자가 최소 2개(프로그램명, target) 이상이어야 실행 가능
	if (argc < 2)
		return (0);

	// 첫 번째 인자(argv[1])는 목표 합(target)
	int target = atoi(argv[1]);

	// 나머지 인자들의 개수 (전체 인자 수 - 프로그램명 - target)
	int cnt = argc - 2;

	// 입력 숫자들을 저장할 배열과, 결과를 담을 버퍼 메모리 할당
	int *nums = malloc(sizeof(int) * cnt);
	int *buffer = malloc(sizeof(int) * cnt);

	// 메모리 할당 실패 시 프로그램 종료 (예외 처리)
	if (!nums || !buffer)
		return (1);

	// 명령줄 인자로 들어온 문자열들을 정수로 변환하여 nums 배열에 저장
	int i = 0;
	while (i < cnt)
	{
		// argv[0]은 실행파일명, argv[1]은 target이므로 숫자는 argv[2]부터 시작
		nums[i] = atoi(argv[i + 2]);
		i++;
	}

	// 재귀 탐색 시작
	// idx: 0, current_sum: 0, buf_idx: 0 부터 시작
	solve(cnt, nums, target, 0, 0, buffer, 0);

	// 사용한 메모리 해제 (누수 방지)
	free(nums);
	free(buffer);

	return (0);
}