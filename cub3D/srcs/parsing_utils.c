#include "cub3d.h"

static void	free_split(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static int	is_valid_color_format(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str) return (0);
	// Handle whitespace at start/end if needed? ft_atoi handles leading space.
	// But strictly, we should ensure only digits and maybe spaces.
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

	if (*color_field != -1)
		return (-1);

	tokens = ft_split(rgb_str, ',');
	if (!tokens)
		return (-1);

	// Check if we have exactly 3 tokens
	if (!tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
		ret_val = -1;
	else if (!is_valid_color_format(tokens[0]) ||
			 !is_valid_color_format(tokens[1]) ||
			 !is_valid_color_format(tokens[2]))
	{
		ret_val = -1;
	}
	else
	{
		r = ft_atoi(tokens[0]);
		g = ft_atoi(tokens[1]);
		b = ft_atoi(tokens[2]);
		if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
			ret_val = -1;
		else
			*color_field = ((r << 16) | (g << 8) | b);
	}

	free_split(tokens);
	return (ret_val);
}