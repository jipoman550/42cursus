#include "cub3d.h"
// #include "libft.h" // libft가 준비되면 주석 해제

/*
** libft가 준비되면 아래 임시 함수들은 제거하고 libft 헤더를 인클루드하세요.
*/
// START: libft 임시 함수들
#include <string.h> // strchr, strcmp 사용을 위해 임시 인클루드

static int is_digit_str(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

// 매우 간단한 버전의 atoi, 실제 프로젝트에서는 libft의 것을 사용하세요.
static int simple_atoi(const char *str)
{
    long res = 0;
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + (*str - '0');
        if (res > 2147483647)
            return (-1); // Overflow
        str++;
    }
    return ((int)res);
}

static void free_tokens(char **tokens)
{
    int i = 0;
    if (!tokens)
        return;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

// 매우 간단한 버전의 ft_split. 실제 libft의 함수를 사용해야 합니다.
// 이 함수는 단지 ','를 기준으로 3개의 문자열로 나누는 것을 가정합니다.
static char **simple_split(const char *str, char c)
{
    char **result;
    const char *start;
    const char *end;
    int i = 0;

    result = (char **)malloc(sizeof(char *) * 4);
    start = str;
    while (i < 3)
    {
        end = strchr(start, c);
        if (i < 2 && !end) { free(result); return (NULL); }
        
        size_t len = (end) ? (size_t)(end - start) : strlen(start);
        result[i] = (char *)malloc(len + 1);
        memcpy(result[i], start, len);
        result[i][len] = '\0';
        
        if (!end) break;
        start = end + 1;
        i++;
    }
    if (i != 2) { free_tokens(result); return (NULL); }
    result[3] = NULL;
    return result;
}

// END: libft 임시 함수들


/**
 * @brief "R,G,B" 형태의 문자열을 파싱하여 int로 합치는 함수
 * @param color_field 색상 값을 저장할 변수의 주소 (e.g., &game->map.floor_color)
 * @param rgb_str "R,G,B" 형식의 색상 문자열
 * @return 성공 시 0, 실패 시 -1
 */
int parse_color(int *color_field, const char *rgb_str)
{
    char **tokens;
    int r, g, b;
    int ret_val = 0;

    if (*color_field != -1) // 이미 색상이 설정되었다면 에러
        return (-1);

    tokens = simple_split(rgb_str, ','); // 실제로는 ft_split 사용
    if (!tokens || !tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
    {
        ret_val = -1;
    }
    else if (!is_digit_str(tokens[0]) || !is_digit_str(tokens[1]) || !is_digit_str(tokens[2]))
    {
        ret_val = -1; // 숫자가 아닌 문자가 포함됨
    }
    else
    {
        r = simple_atoi(tokens[0]); // 실제로는 ft_atoi 사용
        g = simple_atoi(tokens[1]);
        b = simple_atoi(tokens[2]);
        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
            ret_val = -1; // RGB 값의 범위가 유효하지 않음
        else
            *color_field = ((r << 16) | (g << 8) | b);
    }
    
    if (tokens)
        free_tokens(tokens);
    return (ret_val);
}