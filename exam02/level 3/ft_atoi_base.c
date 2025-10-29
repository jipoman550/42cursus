/*
1. str_base가 2~16인지 확인
2. 음수인지 확인
3. 진법변환
4. 음수플래그 * 변환수
*/

int	ft_atoi_base(const char *str, int str_base)
{
	int	result;
	int	sign;
	int	digit_val;

	result = 0;
	sign = 1;

	if (str_base < 2 || str_base > 16)
	{
		return (0);
	}

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			digit_val = *str - '0';
		}
		else if (*str >= 'a' && *str <= 'f')
		{
			digit_val = *str - 'a' + 10;
		}
		else if (*str >= 'A' && *str <= 'F')
		{
			digit_val = *str - 'A' + 10;
		}
		else
		{
			break;
		}

		if (digit_val >= str_base)
		{
			break;
		}

		result = result * str_base + digit_val;

		str++;
	}
	return (result * sign);
}

/*
1. 문제가 2진수 ~ 16진수 형태의 string이 들어오면 10진수 int 형으로 반환하는 건가요?
네, 정확합니다. ft_atoi_base 함수는 str이라는 문자열(string)과 str_base라는 진수(base)를 인자로 받아서, str이 나타내는 str_base 진수의 숫자를 10진수 정수(int)로 변환하여 반환하는 함수입니다.

예를 들어:

ft_atoi_base("101", 2)를 호출하면, 2진수 "101"을 10진수 5로 변환하여 반환합니다.

ft_atoi_base("A", 16)를 호출하면, 16진수 "A"를 10진수 10으로 변환하여 반환합니다.

ft_atoi_base("1f", 16)를 호출하면, 16진수 "1f"를 10진수 31로 변환하여 반환합니다.

ft_atoi_base("-1a", 16)를 호출하면, 16진수 "-1a"를 10진수 -26으로 변환하여 반환합니다.

함수 내의 result = result * str_base + digit_val; 이 부분이 핵심 변환 로직인데, 이는 각 자릿수를 해당 진수의 거듭제곱과 곱해서 더하는 과정을 효율적으로 수행하는 방법입니다.

2. else { break; } 와 if (digit_val >= str_base) { break; } 에 대해 잘 모르겠습니다.
이 두 break 문은 유효하지 않은 문자가 나왔을 때 변환을 중단하기 위한 조건입니다.

else { break; }
C

        else
        {
            break; // 현재 문자가 숫자(0-9)도, 소문자 알파벳(a-f)도, 대문자 알파벳(A-F)도 아닐 경우 반복 중단
        }
이 else 블록은 현재 *str이 가리키는 문자가 '0'부터 '9' 사이의 숫자도 아니고, 'a'부터 'f' 사이의 소문자 알파벳도 아니고, 'A'부터 'F' 사이의 대문자 알파벳도 아닐 경우 실행됩니다.
즉, 입력 문자열에 숫자를 나타내는 유효한 문자가 아닌 다른 문자(예: 공백, 기호, 'g' 이상의 알파벳 등)가 나타나면, 더 이상 변환할 수 없으므로 while 루프를 즉시 종료시키는 역할을 합니다.

예를 들어, ft_atoi_base("123abc", 16) 이라면 "123"까지는 변환되다가 'a'를 만나면 다음 else if 블록에서 처리되지만, 만약 ft_atoi_base("123 G", 16) 이라면 '3'까지 변환 후 공백 ' '을 만나면서 이 else 블록에 의해 루프가 중단됩니다.

if (digit_val >= str_base) { break; }
C

        if (digit_val >= str_base)
        {
            break; // 변환된 자릿값(digit_val)이 현재 진법(str_base)보다 크거나 같을 경우 반복 중단
        }
이 if 블록은 현재 문자를 10진수 값으로 변환한 digit_val이 현재 str_base 진법에서 유효한 숫자인지 확인합니다. 만약 digit_val이 str_base보다 크거나 같으면, 해당 문자는 주어진 str_base 진법에서는 유효하지 않은 숫자이므로, 역시 while 루프를 즉시 종료시킵니다.

예를 들어:

ft_atoi_base("123", 2)를 생각해봅시다.

'1'은 digit_val = 1입니다. 1 < 2이므로 통과.

'2'는 digit_val = 2입니다. 2 >= 2이므로 이 if 문에서 break가 걸립니다. 2진수에는 '2'라는 숫자가 없기 때문입니다.

ft_atoi_base("1a", 10)을 생각해봅시다.

'1'은 digit_val = 1입니다. 1 < 10이므로 통과.

'a'는 digit_val = 10입니다. 10 >= 10이므로 이 if 문에서 break가 걸립니다. 10진수에는 'a'라는 숫자가 없기 때문입니다. (물론 'a'는 앞의 if-else if 체인에서 '0-9' 범위에 속하지 않아 이미 걸러질 수도 있지만, 이 검사는 특히 str_base가 10 미만일 때 중요합니다.)

결론적으로, 이 두 break 문은 입력 문자열 str이 주어진 str_base 진법의 규칙에 맞지 않는 문자를 포함할 경우, 잘못된 변환이 진행되는 것을 막고 유효한 부분까지만 처리하도록 하는 안전장치 역할을 합니다.

*/