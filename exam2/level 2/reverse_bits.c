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