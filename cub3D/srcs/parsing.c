#include "cub3d.h"
#include <stdio.h>

/*
** libft가 준비되면 아래 주석들을 해제하세요.
** #include "libft.h" 
*/

// 임시 t_list 구조체 및 함수. 실제로는 libft의 것을 사용하세요.
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}               t_list;
// ... ft_lstnew, ft_lstadd_back, ft_lstsize, ft_lstclear 등 필요 ...


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
		return (-1); // 에러: 파일 열기 실패

	// line = get_next_line(fd);
	// while (line)
	// {
	// 	if (parse_line(line, game, &config_count, &map_lines) == -1)
	// 	{
	// 		free(line);
	// 		// ft_lstclear(&map_lines, free);
	// 		return (-1); // 에러: 파싱 중 오류 발생
	// 	}
	// 	free(line);
	// 	line = get_next_line(fd);
	// }
	close(fd);

	if (convert_map_list_to_array(game, map_lines) == -1)
		return (-1); // 에러: 맵 변환 실패

	// ft_lstclear(&map_lines, free);
	return (validate_map_and_player(game));
}

/**
 * @brief 한 줄을 파싱하여 정보를 저장하거나 맵 라인 리스트에 추가
 */
static int parse_line(char *line, t_game *game, int *config_count, t_list **map_lines)
{
	char	**tokens;
	int		is_map_line = 0;

	// tokens = ft_split(line, ' ');
	// if (!tokens) return (-1); // Malloc 에러
	tokens = NULL; // 임시

	if (!tokens[0]) // 빈 줄
	{
		// free_tokens(tokens);
		return (0);
	}

	if (*config_count == 6) // 모든 설정이 끝났으면 맵 라인으로 간주
		is_map_line = 1;
	else if (strcmp(tokens[0], "NO") == 0) game->map.no_path = strdup(tokens[1]);
	else if (strcmp(tokens[0], "SO") == 0) game->map.so_path = strdup(tokens[1]);
	else if (strcmp(tokens[0], "WE") == 0) game->map.we_path = strdup(tokens[1]);
	else if (strcmp(tokens[0], "EA") == 0) game->map.ea_path = strdup(tokens[1]);
	else if (strcmp(tokens[0], "F") == 0) parse_color(&game->map.floor_color, tokens[1]);
	else if (strcmp(tokens[0], "C") == 0) parse_color(&game->map.ceil_color, tokens[1]);
	else if (strchr(" 01NSWE", line[0])) // 맵 라인 시작 가능성
		is_map_line = 1;
	else
	{
		// free_tokens(tokens);
		return (-1); // 잘못된 식별자
	}
	
	if (!is_map_line)
		(*config_count)++;
	else
	{
		// ft_lstadd_back(map_lines, ft_lstnew(ft_strdup(line)));
	}
	// free_tokens(tokens);
	return (0);
}


/**
 * @brief 맵 라인의 t_list를 2D char 배열로 변환하고, 맵을 사각형으로 만듦
 */
static int convert_map_list_to_array(t_game *game, t_list *map_lines)
{
	int		i;
	t_list	*current;
	
	// game->map.height = ft_lstsize(map_lines);
	// if (game->map.height == 0) return (-1);
	// game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	// if (!game->map.grid) return (-1);

	// game->map.width = 0;
	current = map_lines;
	while (current)
	{
		// if (strlen(current->content) > game->map.width)
		// 	game->map.width = strlen(current->content);
		current = current->next;
	}

	i = 0;
	current = map_lines;
	while (current)
	{
		// game->map.grid[i] = (char *)malloc(game->map.width + 1);
		// if (!game->map.grid[i]) return (-1);
		// // strncpy(game->map.grid[i], current->content, game->map.width);
		// // 나머지 공간을 공백으로 채움 (' ')
		// for (int j = strlen(current->content); j < game->map.width; j++)
		// 	game->map.grid[i][j] = ' ';
		// game->map.grid[i][game->map.width] = '\0';
		current = current->next;
		i++;
	}
	// game->map.grid[i] = NULL;
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
			if (!strchr(" 01NSWE", game->map.grid[y][x]))
				return (-1); // 유효하지 않은 문자
			if (strchr("NSWE", game->map.grid[y][x]))
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				player_dir = game->map.grid[y][x];
				player_count++;
			}
			// '0' 또는 플레이어 위치가 가장자리나 공백에 닿아있는지 검사
			if (strchr("0NSWE", game->map.grid[y][x]))
			{
				if (y == 0 || y == game->map.height - 1 || x == 0 || x == game->map.width - 1 ||
					game->map.grid[y-1][x] == ' ' || game->map.grid[y+1][x] == ' ' ||
					game->map.grid[y][x-1] == ' ' || game->map.grid[y][x+1] == ' ')
					return (-1); // 맵이 벽으로 둘러싸여 있지 않음
			}
			x++;
		}
		y++;
	}
	if (player_count != 1) return (-1); // 플레이어가 없거나 1명 초과
	
	init_player_direction(&game->player, player_dir);
	return (0);
}

/**
 * @brief 플레이어 시작 방향에 따라 방향/카메라평면 벡터 초기화
 */
static void init_player_direction(t_player *player, char dir)
{
	if (dir == 'N') { player->dir_y = -1; player->plane_x = 0.66; }
	else if (dir == 'S') { player->dir_y = 1; player->plane_x = -0.66; }
	else if (dir == 'W') { player->dir_x = -1; player->plane_y = -0.66; }
	else if (dir == 'E') { player->dir_x = 1; player->plane_y = 0.66; }
}
