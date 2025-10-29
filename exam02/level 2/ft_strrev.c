char *ft_strrev(char *str)
{
	int i;
	int len;
	char tmp;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	//len = len / 2;
	//whlie (i < len) 1번쨰 <-> 마지막 swap 이니까 /2 해줘서 실행횟수를 정해줘도 됨.
	while (i < len - 1)
	{
		tmp = str[i];
		str[i] = str[len - 1];
		str[len - 1] = tmp;
		i++;
		len--;
	}
	return (str);
}
#include <stdio.h>

int main()
{
	char s[] = "hello";
	ft_strrev(s);
	printf("%s\n", s);

	return 0;
}