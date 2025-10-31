#include "permutations.h"

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

char *ft_strdup(char *src)
{
	int len = ft_strlen(src);
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

void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

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

void print_str(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void reverse(char *str, int start, int end)
{
	while (start < end)
	{
		swap(&str[start], &str[end]);
		start++;
		end--;
	}
}

int next_permutation(char *str, int len)
{
	// 1. 뒤에서부터 str[i] < str[i + 1]인 '피벗' 인덱스 i 착기
	int i = len - 2;
	while (i >= 0 && str[i] >= str[i + 1])
		i--;

	// i < 0 이면, 전체가 내림차순 정렬된 상태(마지막 순열)
	if (i < 0)
		return 0;

	// 2. i 오른쪽에서 str[i]보다 크면서 가장 작은 값(가장 오른쪽에 위치한)을 str[j]로 찾기
	int j = len - 1;
	while (str[j] <= str[i])
		j--;

	// 3. str[i]와 str[j] 교환
	swap(&str[i], &str[j]);

	// 4. i + 1부터 끝까지 역순으로 뒤집어 (오름차순 정렬 효과) 가장 작은 접미사를 만듬
	reverse(str, i + 1, len - 1);

	return 1;
}

int main(int argc, char **argv)
{
	// 1. 인자 개수 확인
	if (argc != 2)
		return 0;

	// 2. 입력 문자열 복사 및 검증
	char *str = ft_strdup(argv[1]);
	if (!str)
		return 1;

	int len = ft_strlen(str);

	// 빈 문자열 처리
	if (len == 0)
	{
		write(1, "\n", 1);
		free(str);
		return 0;
	}

	// 3. 사전순 출력을 위해 문자열을 가장 작은 순열(정렬된 상태)로 만들기
	sort_string(str);

	// 4. 첫 번째 순열 출력
	print_str(str);

	// 5. 다음 순열들을 반복적으로 생성하고 출력
	while (next_permutation(str, len))
	{
		print_str(str);
	}

	free(str);
	return 0;
}
