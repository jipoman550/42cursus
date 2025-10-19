/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:58:57 by sisung            #+#    #+#             */
/*   Updated: 2025/10/18 22:38:33 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 문자열이 숫자로만 구성되어 있는지 확인하는 유틸리티
static bool is_valid_digit(char *str)
{
    // ' ' (공백)이나 '-' (음수)가 포함되어서는 안 됩니다.
	// '+' 가 있는 경우랑 없는 경우의 양수를 구분해서 처리해야될까?
    // 여기서는 isdigit() 함수와 비슷한 역할을 하는 코드가 들어갑니다.
	size_t	i;

	if (!str || *str == '\0')
		return (false);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

// 문자열을 long long으로 변환하며 오버플로우 여부를 체크합니다.
// is_overflow 포인터를 통해 오류 정보를 전달합니다.
static long long	ft_atoll_safe(const char *str, bool *is_overflow)
{
	long long	result;

	result = 0;
	*is_overflow = false;
	while (*str)
	{
		// 이 부분이 이해하기 쉽지 않음.
		if (result > LLONG_MAX / 10
			|| (result == LLONG_MAX / 10 && *str - '0' > LLONG_MAX % 10))
        {
            *is_overflow = true;
            return (LLONG_MAX); // 오버플로우 발생 시 LLONG_MAX 반환 (오류 플래그와 함께)
        }
		result = result * 10 + (*str - '0');
        str++;
	}
	return (result);
}

// 문자열 인자를 양의 정수로 파싱하며 유효성 검사를 수행하는 함수
long long ft_parse_long(char *str)
{
    long long	num;
	bool		is_overflow;

    // 1. is_valid_digit을 사용하여 문자열이 유효한지 확인
    if (!is_valid_digit(str))
	{
		printf("Error: Argument contains non-digit characters.\n");
        return (-1); // 에러 표시
	}

    // 2. atoll 또는 커스텀 함수로 문자열을 long long으로 변환.
	// atoll 사용불가능임.
    num = ft_atoll_safe(str, &is_overflow);

    // 3. 오버플로우 또는 0이거나 음수인 경우 체크
	if (is_overflow)
    {
		printf("Error: Argument value exceeds maximum limit.\n");
        return (-1);
    }

	// (예외: must_eat_count는 0이 '무한'을 의미할 수 있으나, 다른 인자는 1 이상이어야 함)
	// 참고: must_eat_count를 제외한 모든 인자는 0보다 커야 합니다.
    // must_eat_count가 0일 경우 (인자가 5개일 때) init 함수에서 처리할 것이므로,
    // ft_parse_long은 0이 입력되는 경우를 일단 에러로 간주하는 것이 안전합니다
    if (num <= 0)
	{
        // 다만, 인자 자체가 "0"인 경우는 (number_of_philosophers=0은 불가능)도 처리해야 함.
        if (*str == '0')
             printf("Error: Argument cannot be zero.\n");
        else
             printf("Error: Argument must be a positive integer.\n");
        return (-1);
	}

    return (num);
}
