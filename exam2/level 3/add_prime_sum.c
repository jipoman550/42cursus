/*
1. parmeter 개수 2개가 아니면 예외처리
2. ft_atoi를 통해 integer로 변환
3. 변환한 수가 <= 0 이면 예외처리
4. 변환한 수보다 작거나 같은 prime number 찾아서 sum 하기
5. sum = 0 이면 바로 write 찍기
6. sum 을 string 형태로 바꾸어서(ft_putnbr) write 찍기.
*/

#include <unistd.h> // write 함수를 위해 포함

// 숫자가 양의 정수 문자열인지 확인하고 정수로 변환하는 함수
// 유효하지 않으면 0을 반환 (과제 조건에 따라)
int ft_atoi_positive(char *s)
{
    int num = 0;
    int i = 0;

    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
        {
            return 0; // 숫자가 아님
        }
        num = num * 10 + (s[i] - '0');
        i++;
    }
    if (num <= 0)
    {
        return 0; // 양의 정수가 아님
    }
    return num;
}

// 주어진 숫자가 소수인지 판별하는 함수
// 소수이면 1, 아니면 0을 반환
int is_prime(int n)
{
    if (n < 2)
        return 0; // 0과 1은 소수가 아님

    int i = 2;
    while (i * i <= n)
    {
        if (n % i == 0)
        {
            return 0; // 나누어 떨어지면 소수가 아님
        }
        i++;
    }
    return 1; // 소수임
}

// 정수를 문자열로 변환하여 출력하는 함수
void ft_putnbr(int n)
{
    if (n == 0)
    {
        write(1, "0", 1);
        return;
    }

    // 숫자의 자릿수 계산
    int temp_n = n;
    int digits = 0;
    while (temp_n > 0)
    {
        temp_n /= 10;
        digits++;
    }

    // 숫자를 문자열로 저장할 배열 (최대 10자릿수 + 널 종료)
    // int 최대값 2,147,483,647 (10자리)
    char buffer[11]; // 10자리 + 널 문자
    buffer[digits] = '\0';

    int i = digits - 1;
    while (i >= 0)
    {
        buffer[i] = (n % 10) + '0';
        n /= 10;
        i--;
    }
    write(1, buffer, digits);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        write(1, "0\n", 2);
        return 0;
    }

    int num = ft_atoi_positive(argv[1]);
    if (num == 0) // ft_atoi_positive에서 유효성 검사 실패 시 0 반환
    {
        write(1, "0\n", 2);
        return 0;
    }

    int sum = 0;
    int n = 2;
    while (n <= num)
    {
        if (is_prime(n))
        {
            sum += n;
        }
        n++;
    }

    ft_putnbr(sum);
    write(1, "\n", 1);

    return 0;
}


/*#include <unistd.h>

// no use function
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		write(1, "0\n", 2);
		return 0;
	}

	char *s = argv[1];
	int num = 0;
	int i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			write(1, "0\n", 2);
			return 0;
		}
		num = num * 10 + (s[i] - '0');
		i++;
	}

	if (num <= 0)
	{
		write(1, "0\n", 2);
		return 0;
	}

	int sum = 0;
	int n = 2;
	while (n <= num)
	{
		int is_prime_flag = 0;
		if (n < 2)
			is_prime_flag = 1;
		i = 2;
		while (i * i <= n)
		{
			if (n % i == 0)
			{
				i++;
				is_prime_flag = 1;
				break;
			}
			i++;
		}
		if (!is_prime_flag)
			sum += n;
		n++;
	}

	if (sum == 0)
	{
		write(1, "0\n", 2);
		return 0;
	}

	int sum_tmp = sum;
	int digit = 0;
	while (sum_tmp > 0)
	{
		digit++;
		sum_tmp = sum_tmp / 10;
	}
	char ret[digit + 1];
	ret[digit] = '\0';

	sum_tmp = sum;
	i = digit - 1;
	while (i >= 0)
	{
		ret[i] = (sum_tmp % 10) + '0';
		sum_tmp /= 10;
		i--;
	}
	write(1, ret, digit);
	write(1, "\n", 1);
	return 0;
}*/