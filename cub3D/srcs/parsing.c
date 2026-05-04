/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:42:55 by sisung            #+#    #+#             */
/*   Updated: 2026/05/04 17:21:26 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

// Forward declarations
// static 함수들은 이 파일 내부에서만 사용되므로 헤더로 옮기지 않고 여기에 선언합니다.
static int	parse_line(char *line, t_game *game, int *config_count, t_list **map_lines);
static int	convert_map_list_to_array(t_game *game, t_list *map_lines);
static int	validate_map_and_player(t_game *game);
static void	init_player_direction(t_player *player, char dir);
int	check_extension(const char *path, const char *ext);
// parse_color는 parsing_utils.c에 정의되어 있고 외부에서 사용되므로 cub3d.h로 이동했습니다.

/**
 * @brief .cub 맵 파일을 파싱하여 게임 구조체에 정보를 저장하는 메인 함수
 * @param file_path 열어야 할 맵 파일의 경로
 * @param game 파싱된 데이터를 저장할 게임 구조체 포인터
 * @return 파싱 성공 시 0, 실패 시 -1 반환
 */
int	parse_map(const char *file_path, t_game *game)
{
	int		fd;
	char	*line;
	int		config_count = 0;
	t_list	*map_lines = NULL;

	// 색상 초기값을 -1로 설정하여 중복/미설정 확인.
	// init_game_struct(&game) 에서 이미 해줌. 중복인듯
	//game->map.floor_color = -1;
	//game->map.ceil_color = -1;
	// 파일 열기
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);

	// GNL을 사용하여 파일 끝까지 한 줄씩 읽기
	line = get_next_line(fd);
	while (line)
	{
		// 읽은 줄을 파싱 (설정 정보 또는 맵 데이터)
		if (parse_line(line, game, &config_count, &map_lines) == -1)
		{
			free(line);
			ft_lstclear(&map_lines, free);
			// 남은 gnl처리 안해서 리크
			line = get_next_line(fd);
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			};
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);

	// 6가지 설정(동서남북 텍스처 + 천장/바닥 색상)이 모두 완료되었는지 확인
	if (config_count != 6)
	{
		ft_lstclear(&map_lines, free);
		return (-1);
	}

	// 리스트에 저장된 맵 데이터를 2차원 배열로 변환
	if (convert_map_list_to_array(game, map_lines) == -1)
	{
		ft_lstclear(&map_lines, free);
		return (-1);
	}

	// 리스트 메모리 해제
	ft_lstclear(&map_lines, free);
	// 맵 유효성(벽, 플레이어 등) 검사
	return (validate_map_and_player(game));
}

/**
 * @brief 파일의 한 줄을 분석하여 설정 정보나 맵 데이터를 처리
 * @param line 파일에서 읽은 한 줄 문자열
 * @param game 게임 구조체 포인터
 * @param config_count 현재까지 처리된 설정 개수 포인터
 * @param map_lines 맵 데이터를 저장할 리스트의 주소
 * @return 성공 시 0, 실패 시 -1 반환
 */
static int	parse_line(char *line, t_game *game, int *config_count, t_list **map_lines)
{
	char	**tokens;
	char	*trimmed_line;
	int		is_map_line = 0;

	// 개행 문자 제거
	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
		return (-1);
	if (ft_strlen(trimmed_line) == 0) // 빈 줄은 무시
	{
		free(trimmed_line);
		if (*config_count == 6)
		{
			/*
			** 빈 줄을 무시하지 않고 빈 문자열로 리스트에 추가!
			** 나중에 convert_map_list_to_array에서 game->map.width 만큼의 공백으로 쫙 채워짐
			*/
			ft_lstadd_back(map_lines, ft_lstnew(ft_strdup("")));
		}
		return (0);
	}

	// 설정이 모두 완료되었으면 이후 라인은 맵 데이터로 간주
	if (*config_count == 6)
		is_map_line = 1;
	else
	{
		// 공백 기준으로 문자열 분리
		tokens = ft_split(trimmed_line, ' ');
		if (!tokens)
		{
			free(trimmed_line);
			return (-1);
		}
		if (!tokens[0])
		{
			// 빈 줄 처리 (안전 장치)
			free(trimmed_line);
			free(tokens);
			return (0);
		}
		/*
		** 식별자 라인은 반드시 [식별자] [데이터] 두 토큰만 존재해야 함
		** tokens[2]가 존재한다면 'NO ./path garbage'와 같은 오류 상황임
		*/
		//if (tokens[0] && tokens[1] && tokens[2])
		//{
		//	free_split(tokens);
		//	free(trimmed_line);
		//	// write(2, "Error\nInvalid line configuration\n", 33);
		//	return (-1);
		//}
		/* 3. 데이터 개수 초과 검사 (Misconfiguration) */
		if (tokens[1] != NULL && tokens[2] != NULL)
		{
			free_split(tokens);
			free(trimmed_line);
			/* 42 규칙: 에러 발생 시 명확한 메시지 출력 */
			write(2, "Error\nInvalid line configuration: Too many arguments\n", 53);
			return (-1);
		}

		if (ft_strncmp(tokens[0], "NO", 3) == 0 && tokens[1])
		{
			if (game->map.no_path != NULL)
			{
				free_split(tokens);
				free(trimmed_line);
				// error msg
				return (-1);
			}
			if (!check_extension(tokens[1], ".xpm"))
			{
				free_split(tokens);
				free(trimmed_line);
				// error msg
				return (-1);
			}
			game->map.no_path = ft_strdup(tokens[1]);
		}
		else if (ft_strncmp(tokens[0], "SO", 3) == 0 && tokens[1])
		{
			if (game->map.so_path != NULL)
			{
				free_split(tokens);
				free(trimmed_line);
				return (-1);
			}
			if (!check_extension(tokens[1], ".xpm"))
			{
				free_split(tokens);
				free(trimmed_line);
				// error msg
				return (-1);
			}
			game->map.so_path = ft_strdup(tokens[1]);
		}
		else if (ft_strncmp(tokens[0], "WE", 3) == 0 && tokens[1])
		{
			if (game->map.we_path != NULL)
			{
				free_split(tokens);
				free(trimmed_line);
				return (-1);
			}
			if (!check_extension(tokens[1], ".xpm"))
			{
				free_split(tokens);
				free(trimmed_line);
				// error msg
				return (-1);
			}
			game->map.we_path = ft_strdup(tokens[1]);
		}
		else if (ft_strncmp(tokens[0], "EA", 3) == 0 && tokens[1])
		{
			// [중요] 이미 경로가 존재한다면 이는 중복 설정(Misconfiguration)입니다.
			if (game->map.ea_path != NULL)
			{
				// 스플릿 반환이 배열형태인데 하나만 해제 다른 곳도 다 해야함
				free_split(tokens);
				// free(tokens);		// 현재 줄의 토큰 해제
				free(trimmed_line);	// strtrim한 문자열 해제
				return (-1);		// parse_map으로 에러 리턴 -> main에서 free_game 호출됨
			}
			if (!check_extension(tokens[1], ".xpm"))
			{
				free_split(tokens);
				free(trimmed_line);
				// error msg
				return (-1);
			}
			game->map.ea_path = ft_strdup(tokens[1]);
		}
		else if (ft_strncmp(tokens[0], "F", 2) == 0 && tokens[1])
		{
			if (parse_color(&game->map.floor_color, tokens[1]) == -1)
			{
				free(trimmed_line);
				free_split(tokens);
				return (-1);
			}
		}
		else if (ft_strncmp(tokens[0], "C", 2) == 0 && tokens[1])
		{
			if (parse_color(&game->map.ceil_color, tokens[1]) == -1)
			{
				free(trimmed_line);
				free_split(tokens);
				return (-1);
			}
		}
		// 불필요한거 같음.
		// 설정이 덜 끝났는데 맵 데이터(1, 0 등)가 나오면 맵 시작으로 간주
		//else if (ft_strchr(" 01NSWE", tokens[0][0]))
		//	is_map_line = 1;
		else
		{
			// 알 수 없는 식별자
			free(trimmed_line);
			free_split(tokens);
			return (-1);
		}

		// 토큰 메모리 해제
		free_split(tokens);
	}

	if (!is_map_line)
		(*config_count)++;
	else
	{
		// 맵 라인은 공백이 중요하므로 ft_split/trim 대신 원본 라인 사용
		// 마지막 개행 문자만 제거하여 리스트에 추가
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
 * @brief 연결 리스트로 저장된 맵 데이터를 2차원 배열(grid)로 변환
 * @param game 게임 구조체 포인터
 * @param map_lines 맵 데이터가 담긴 연결 리스트
 * @return 성공 시 0, 실패 시 -1
 */
static int	convert_map_list_to_array(t_game *game, t_list *map_lines)
{
	int		i;
	t_list	*current;
	size_t	len;

	// 맵의 높이 계산
	game->map.height = ft_lstsize(map_lines);
	if (game->map.height == 0)
		return (-1);

	// 높이만큼 포인터 배열 할당
	game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (-1);

	// 맵의 최대 너비 계산
	game->map.width = 0;
	current = map_lines;
	while (current)
	{
		len = ft_strlen((char *)current->content);
		if ((int)len > game->map.width)
			game->map.width = (int)len;
		current = current->next;
	}

	// 각 줄을 최대 너비에 맞춰 할당하고 복사 (남는 공간은 공백 채움)
	i = 0;
	current = map_lines;
	while (current)
	{
		game->map.grid[i] = (char *)malloc(game->map.width + 1);
		if (!game->map.grid[i])
			return (-1); // 실제로는 이전 할당 해제 필요

		ft_strlcpy(game->map.grid[i], (char *)current->content, game->map.width + 1);

		// 나머지 부분을 공백으로 채우기
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
 * @brief 맵의 유효성(벽 밀폐 여부, 유효 문자) 및 플레이어 위치 검사
 * @param game 게임 구조체 포인터
 * @return 맵이 유효하면 0, 아니면 -1 반환
 */
static int	validate_map_and_player(t_game *game)
{
	int		x;
	int		y;
	int		player_count = 0;
	char	player_dir = 0;

	if (!game->map.grid)
		return (-1);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			// 허용되지 않은 문자 검사
			if (game->map.grid[y][x] != ' ' && !ft_strchr("01NSWE", game->map.grid[y][x]))
				return (-1);
			// 플레이어 위치 및 방향 확인
			if (ft_strchr("NSWE", game->map.grid[y][x]))
			{
				if (player_count > 0)
					return (-1); // 플레이어가 2명 이상이면 에러
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				player_dir = game->map.grid[y][x];
				player_count++;
			}
			// 바닥(0)이나 플레이어가 맵 가장자리나 공백과 인접해 있는지 검사 (벽으로 둘러싸여야 함)
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
	// 플레이어가 정확히 1명이어야 함
	// 0명일때 처리해줌
	if (player_count != 1)
		return (-1);

	init_player_direction(&game->player, player_dir);
	return (0);
}

/**
 * @brief 플레이어의 초기 바라보는 방향과 카메라 평면 벡터 설정
 * @param player 플레이어 구조체 포인터
 * @param dir 방향 문자 ('N', 'S', 'W', 'E')
 */
static void	init_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
}

/**
 * @brief 파일 경로가 특정 확장자로 끝나는지 확인하는 함수
 * @param path 검사할 파일 경로 문자열
 * @param ext 확인할 확장자 문자열 (예: ".cub")
 * @return 확장자가 일치하면 1, 그렇지 않으면 0 반환
 */
int	check_extension(const char *path, const char *ext)
{
	size_t	path_len;
	size_t	ext_len;

	// 파일 경로와 확장자의 길이를 구함
	path_len = ft_strlen(path);
	ext_len = ft_strlen(ext);
	// 경로가 확장자보다 짧으면 일치할 수 없음
	if (path_len < ext_len)
		return (0);
	// 경로의 끝부분이 확장자와 일치하는지 비교
	return (ft_strncmp(path + path_len - ext_len, ext, ext_len + 1) == 0);
}
