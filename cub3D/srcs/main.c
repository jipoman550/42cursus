/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 23:25:23 by sisung            #+#    #+#             */
/*   Updated: 2026/05/02 15:40:55 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 파일 경로가 특정 확장자로 끝나는지 확인하는 함수
 * @param path 검사할 파일 경로 문자열
 * @param ext 확인할 확장자 문자열 (예: ".cub")
 * @return 확장자가 일치하면 1, 그렇지 않으면 0 반환
 */
static int	check_extension(const char *path, const char *ext)
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

/**
 * @brief t_game 구조체를 0으로 초기화하고 기본값을 설정하는 함수
 * @param game 초기화할 게임 구조체 포인터
 */
static void	init_game_struct(t_game *game)
{
	// 구조체 전체 메모리를 0으로 초기화
	ft_memset(game, 0, sizeof(t_game));
	// 천장과 바닥 색상을 -1로 설정 (파싱되지 않았음을 표시)
	game->map.floor_color = -1;
	game->map.ceil_color = -1;
}

/**
 * @brief 프로그램의 진입점 (Entry Point)
 * @param argc 인자 개수
 * @param argv 인자 문자열 배열
 * @return 프로그램 종료 코드 (0: 성공, 1: 에러)
 */
int	main(int argc, char **argv)
{
	t_game	game;

	// 인자가 2개가 아니면 사용법 출력 후 종료
	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
		return (1);
	}
	// 파일 확장자가 .cub인지 확인
	if (!check_extension(argv[1], ".cub"))
	{
		write(2, "Error\nInvalid file extension (need .cub)\n", 41);
		return (1);
	}
	// 게임 구조체 초기화
	init_game_struct(&game);
	// 맵 파일 파싱 및 유효성 검사
	if (parse_map(argv[1], &game) == -1)
	{
		write(2, "Error\nFailed to parse map\n", 26);
		free_game(&game);
		return (1);
	}
	// MLX 라이브러리 초기화 (윈도우 생성 등)
	if (init_game(&game) == -1)
	{
		write(2, "Error\nFailed to initialize MLX\n", 30);
		free_game(&game);
		return (1);
	}
	// 텍스처 이미지 로드
	if (load_textures(&game) == -1)
	{
		free_game(&game);
		return (1);
	}
	// 게임 루프 시작 (이벤트 처리 및 렌더링)
	start_game_loop(&game);
	return (0);
}