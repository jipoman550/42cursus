#include <stddef.h>

size_t ft_strcspn(const char *s, const char *reject)
{
	size_t i, j;

	i = 0;

	while (s[i] != '\0')
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j++])
				return (i);
		}
		i++;
	}

	return (i);
}

/*ft_strcspn 함수 설명
ft_strcspn 함수는 표준 C 라이브러리의 strcspn 함수와 동일하게 동작하도록 구현되었습니다. 이 함수는 두 개의 문자열을 입력으로 받습니다:

s: 검사할 문자열입니다.

reject: 찾을 문자들을 포함하는 문자열입니다.

함수의 동작 방식:

s 문자열의 시작부터 탐색을 시작합니다.

s의 각 문자를 reject 문자열의 모든 문자와 비교합니다.

만약 s에서 reject 문자열에 있는 어떤 문자라도 처음으로 발견되면, 해당 문자가 나타나기 전까지의 s 문자열 길이를 반환합니다. 이 길이는 reject 문자열에 있는 문자를 포함하지 않습니다.

만약 s 문자열의 끝까지 reject 문자열의 어떤 문자도 발견되지 않으면, s 문자열의 전체 길이를 반환합니다.

예시:

ft_strcspn("hello world", "aeiou")는 "h" 다음에 "e"가 있으므로 1을 반환합니다.

ft_strcspn("programming", "xyz")는 programming에 x, y, z가 없으므로 11을 반환합니다.

ft_strcspn("apple", "p")는 "a" 다음에 "p"가 있으므로 1을 반환합니다.

이 코드는 size_t 타입을 사용하기 위해 <stddef.h> 헤더 파일을 포함하고 있으며, 문제에서 요구하는 프로토타입을 따릅니다.*/