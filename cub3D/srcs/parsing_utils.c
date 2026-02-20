#include "cub3d.h"

/**
 * @brief ft_split으로 할당된 문자열 배열 메모리를 해제
 * @param tokens 해제할 문자열 배열
 */
static void	free_split(char **tokens)
{
	int	i;

	// 배열이 NULL이면 리턴
	if (!tokens)
		return ;
	i = 0;
	// 각 문자열 메모리 해제
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	// 배열 자체 메모리 해제
	free(tokens);
}

/**
 * @brief 문자열이 숫자와 공백으로만 구성되어 있는지 확인
 * @param str 검사할 문자열
 * @return 유효하면 1, 아니면 0
 */
static int	is_valid_color_format(char *str)
{
	int	i;

	i = 0;
	// 빈 문자열 체크
	if (!str || !*str) return (0);
	// 문자열 순회하며 숫자나 공백/개행이 아닌 문자가 있는지 확인
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief "R,G,B" 형태의 문자열을 파싱하여 int로 합치는 함수
 * @param color_field 색상 값을 저장할 변수의 주소 (e.g., &game->map.floor_color)
 * @param rgb_str "R,G,B" 형식의 색상 문자열
 * @return 성공 시 0, 실패 시 -1
 */
int	parse_color(int *color_field, const char *rgb_str)
{
	char	**tokens;
	int		r, g, b;
	int		ret_val = 0;

	// 이미 색상이 설정되어 있다면 중복 설정 에러
	if (*color_field != -1)
		return (-1);

	// 콤마(,)를 기준으로 문자열 분리
	tokens = ft_split(rgb_str, ',');
	if (!tokens)
		return (-1);

	// 토큰이 정확히 3개(R, G, B)인지 확인
	if (!tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
		ret_val = -1;
	// 각 토큰이 숫자로만 구성되어 있는지 확인
	else if (!is_valid_color_format(tokens[0]) ||
			 !is_valid_color_format(tokens[1]) ||
			 !is_valid_color_format(tokens[2]))
	{
		ret_val = -1;
	}
	else
	{
		// 문자열을 정수로 변환
		r = ft_atoi(tokens[0]);
		g = ft_atoi(tokens[1]);
		b = ft_atoi(tokens[2]);
		// RGB 범위(0~255) 확인
		if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
			ret_val = -1;
		else
			// 비트 연산으로 RGB 값을 하나의 int로 병합 (0x00RRGGBB)
			*color_field = ((r << 16) | (g << 8) | b);
	}

	// 분리된 토큰 메모리 해제
	free_split(tokens);
	return (ret_val);
}