#include "cub3d.h"
#include <stdio.h>

// Forward declarations
static int	parse_line(char *line, t_game *game, int *config_count, t_list **map_lines);
static int	convert_map_list_to_array(t_game *game, t_list *map_lines);
static int	validate_map_and_player(t_game *game);
static void	init_player_direction(t_player *player, char dir);
int			parse_color(int *color_field, const char *rgb_str);

/**
 * @brief .cub 파일을 파싱하여 t_game 구조체를 채우는 메인 함수
 */
int	parse_map(const char *file_path, t_game *game)
{
	int		fd;
	char	*line;
	int		config_count = 0;
	t_list	*map_lines = NULL;

	game->map.floor_color = -1;
	game->map.ceil_color = -1;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);

	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(line, game, &config_count, &map_lines) == -1)
		{
			free(line);
			ft_lstclear(&map_lines, free);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);

	if (config_count != 6)
	{
		ft_lstclear(&map_lines, free);
		return (-1);
	}

	if (convert_map_list_to_array(game, map_lines) == -1)
	{
		ft_lstclear(&map_lines, free);
		return (-1);
	}

	ft_lstclear(&map_lines, free);
	return (validate_map_and_player(game));
}

/**
 * @brief 한 줄을 파싱하여 정보를 저장하거나 맵 라인 리스트에 추가
 */
static int	parse_line(char *line, t_game *game, int *config_count, t_list **map_lines)
{
	char	**tokens;
	char	*trimmed_line;
	int		is_map_line = 0;

	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
		return (-1);
	if (ft_strlen(trimmed_line) == 0) // 빈 줄
	{
		free(trimmed_line);
		return (0);
	}

	if (*config_count == 6)
		is_map_line = 1;
	else
	{
		tokens = ft_split(trimmed_line, ' ');
		if (!tokens)
		{
			free(trimmed_line);
			return (-1);
		}
		if (!tokens[0])
		{
			// Should be handled by empty line check, but safety first
			free(trimmed_line);
			free(tokens); // ft_split might return non-NULL even for empty string if implementation varies, but here we expect NULL terminated array
			return (0);
		}

		if (ft_strncmp(tokens[0], "NO", 3) == 0 && tokens[1]) game->map.no_path = ft_strdup(tokens[1]);
		else if (ft_strncmp(tokens[0], "SO", 3) == 0 && tokens[1]) game->map.so_path = ft_strdup(tokens[1]);
		else if (ft_strncmp(tokens[0], "WE", 3) == 0 && tokens[1]) game->map.we_path = ft_strdup(tokens[1]);
		else if (ft_strncmp(tokens[0], "EA", 3) == 0 && tokens[1]) game->map.ea_path = ft_strdup(tokens[1]);
		else if (ft_strncmp(tokens[0], "F", 2) == 0 && tokens[1])
		{
			if (parse_color(&game->map.floor_color, tokens[1]) == -1)
			{ free(trimmed_line); int i = 0; while (tokens[i]) free(tokens[i++]); free(tokens); return (-1); }
		}
		else if (ft_strncmp(tokens[0], "C", 2) == 0 && tokens[1])
		{
			if (parse_color(&game->map.ceil_color, tokens[1]) == -1)
			{ free(trimmed_line); int i = 0; while (tokens[i]) free(tokens[i++]); free(tokens); return (-1); }
		}
		else if (ft_strchr(" 01NSWE", tokens[0][0]))
			is_map_line = 1;
		else
		{
			// Unknown identifier
			free(trimmed_line);
			// You need a helper to free split array: ft_free_split(tokens) or manual loop
			int i = 0; while (tokens[i]) free(tokens[i++]); free(tokens);
			return (-1);
		}

		int i = 0; while (tokens[i]) free(tokens[i++]); free(tokens);
	}

	if (!is_map_line)
		(*config_count)++;
	else
	{
		// 맵 라인은 원본 라인에서 개행만 제거한 것을 저장해야 공백 보존 가능
		// BUT ft_split lost spaces. Need line without newline.
		// trimmed_line is line without newline (if only \n at end). but ft_strtrim trims BOTH ends.
		// We only want to trim end newline for map lines usually, or handle trailing spaces consistently.
		// For map, spaces are important.
		// Let's use ft_strdup of line but remove ONLY the last \n if present.

		char *map_content;
		size_t len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			map_content = ft_substr(line, 0, len - 1);
		else
			map_content = ft_strdup(line);

		ft_lstadd_back(map_lines, ft_lstnew(map_content));
	}
	free(trimmed_line);
	return (0);
}

/**
 * @brief 맵 라인의 t_list를 2D char 배열로 변환하고, 맵을 사각형으로 만듦
 */
static int	convert_map_list_to_array(t_game *game, t_list *map_lines)
{
	int		i;
	t_list	*current;
	size_t	len;

	game->map.height = ft_lstsize(map_lines);
	if (game->map.height == 0) return (-1);

	game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid) return (-1);

	game->map.width = 0;
	current = map_lines;
	while (current)
	{
		len = ft_strlen((char *)current->content);
		if ((int)len > game->map.width)
			game->map.width = (int)len;
		current = current->next;
	}

	i = 0;
	current = map_lines;
	while (current)
	{
		game->map.grid[i] = (char *)malloc(game->map.width + 1);
		if (!game->map.grid[i]) return (-1); // Should free previous allocations

		ft_strlcpy(game->map.grid[i], (char *)current->content, game->map.width + 1);

		// Fill remaining with spaces
		int j = ft_strlen((char *)current->content);
		while (j < game->map.width)
			game->map.grid[i][j++] = ' ';
		game->map.grid[i][game->map.width] = '\0';

		current = current->next;
		i++;
	}
	game->map.grid[i] = NULL;
	return (0);
}

/**
 * @brief 맵이 유효한지 (벽으로 둘러싸였는지 등) 검사하고 플레이어 정보를 설정
 */
static int	validate_map_and_player(t_game *game)
{
	int		x, y;
	int		player_count = 0;
	char	player_dir = 0;

	if (!game->map.grid) return (-1);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] != ' ' && !ft_strchr("01NSWE", game->map.grid[y][x]))
				return (-1);
			if (ft_strchr("NSWE", game->map.grid[y][x]))
			{
				if (player_count > 0) return (-1); // 중복 플레이어
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				player_dir = game->map.grid[y][x];
				player_count++;
			}
			if (ft_strchr("0NSWE", game->map.grid[y][x]))
			{
				if (y == 0 || y == game->map.height - 1 || x == 0 || x == game->map.width - 1 ||
					game->map.grid[y-1][x] == ' ' || game->map.grid[y+1][x] == ' ' ||
					game->map.grid[y][x-1] == ' ' || game->map.grid[y][x+1] == ' ')
					return (-1);
			}
			x++;
		}
		y++;
	}
	if (player_count != 1) return (-1);

	init_player_direction(&game->player, player_dir);
	return (0);
}

/**
 * @brief 플레이어 시작 방향에 따라 방향/카메라평면 벡터 초기화
 */
static void	init_player_direction(t_player *player, char dir)
{
	if (dir == 'N') { player->dir_x = 0; player->dir_y = -1; player->plane_x = 0.66; player->plane_y = 0; }
	else if (dir == 'S') { player->dir_x = 0; player->dir_y = 1; player->plane_x = -0.66; player->plane_y = 0; }
	else if (dir == 'W') { player->dir_x = -1; player->dir_y = 0; player->plane_x = 0; player->plane_y = -0.66; }
	else if (dir == 'E') { player->dir_x = 1; player->dir_y = 0; player->plane_x = 0; player->plane_y = 0.66; }
}
