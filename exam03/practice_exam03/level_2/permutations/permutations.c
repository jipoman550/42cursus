#include "permutations.h"

/*
** ft_strlen: 문자열의 길이를 계산합니다.
*/
int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

/*
** ft_strdup: 문자열을 복사하고 새로운 메모리에 할당합니다.
** (할당된 메모리는 호출자가 해제해야 합니다.)
*/
char *ft_strdup(char *src)
{
	int len = ft_strlen(src);
	// calloc 대신 malloc 사용
	char *dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return NULL;
	int i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return dst;
}

/*
** swap: 두 문자(포인터)의 값을 교환합니다.
*/
void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
** reverse: 문자열의 특정 구간(start부터 end까지)을 역순으로 뒤집습니다.
*/
void reverse(char *str, int start, int end)
{
	while (start < end)
	{
		swap(&str[start], &str[end]);
		start++;
		end--;
	}
}

/*
** sort_string: 버블 정렬을 사용하여 문자열을 오름차순으로 정렬합니다.
** (사전순 출력을 위해 초기 순열을 가장 작은 값으로 설정합니다.)
*/
void sort_string(char *str)
{
	int len = ft_strlen(str);
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (str[j] > str[j + 1])
				swap(&str[j], &str[j + 1]);
		}
	}
}

/*
** next_permutation: 현재 문자열에서 사전순으로 바로 다음 순열을 생성합니다.
** 반환값: 1 = 다음 순열 생성 성공, 0 = 마지막 순열
*/
int next_permutation(char *str, int len)
{
	// 1. 뒤에서부터 str[i] < str[i+1]인 '피벗' 인덱스 i를 찾습니다.
	int i = len - 2;
	while (i >= 0 && str[i] >= str[i + 1])
		i--;

	// i < 0 이면, 전체가 내림차순 정렬된 상태(마지막 순열)입니다.
	if (i < 0)
		return 0;

	// 2. i 오른쪽에서 str[i]보다 크면서 가장 작은 값(가장 오른쪽에 위치한)을 str[j]로 찾습니다.
	int j = len - 1;
	while (str[j] <= str[i])
		j--;

	// 3. str[i]와 str[j] 교환
	swap(&str[i], &str[j]);

	// 4. i+1부터 끝까지를 역순으로 뒤집어(오름차순 정렬 효과) 가장 작은 접미사를 만듭니다.
	reverse(str, i + 1, len - 1);

	return 1;
}

/*
** print_str: 문자열을 출력하고 개행 문자를 추가합니다.
*/
void print_str(char *str)
{
	// 함수 허용 목록에 'puts'와 'write'가 있으므로, 출력은 write를 사용합니다.
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

int main(int argc, char **argv)
{
	// [1] 인자 개수 확인
	if (argc != 2)
		return 0;

	// [2] 입력 문자열 복사 및 검증
	char *str = ft_strdup(argv[1]);
	if (!str)
		return 1; // 메모리 할당 실패

	int len = ft_strlen(str);

	// 빈 문자열 처리 (출력 예시가 개행 문자를 요구하므로)
	if (len == 0)
	{
		write(1, "\n", 1);
		free(str);
		return 0;
	}

	// [3] 사전순 출력을 위해 문자열을 가장 작은 순열(정렬된 상태)로 만듭니다.
	sort_string(str);

	// [4] 첫 번째 순열 출력
	print_str(str);

	// [5] 다음 순열들을 반복적으로 생성하고 출력합니다.
	while (next_permutation(str, len))
	{
		print_str(str);
	}

	// [6] 메모리 해제
	free(str);
	return 0;
}
