/*
1. result를 왼쪽으로 << 1 비트연산 (맨 뒤부터 채우기 때문에 8번째 -> 7번째 -> ... -> 2번째 -> 1번쨰)
2. & 1 연산을 통해 맨 오른쪽의 값을 가져옴.
3. result | (octet & 1)을 통해서 result에 저장
4. 다음 자리수 계산을 위한 octet >> 1 연산
*/

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char result = 0;
	int i = 0;

	while (i < 8)
	{
		result = result << 1;

		result = result | (octet & 1);

		octet = octet >> 1;

		i++;
	}
	return (result);
}

#include <stdio.h>

int main()
{
	unsigned char bit = 0;
	unsigned char res = reverse_bits((unsigned char)5);
	int i = 8;
	while (i--)
	{
		bit = (res >> i & 1) + 48;
		printf("%c", bit);
	}
	printf("\n");
}