/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 23:25:23 by sisung            #+#    #+#             */
/*   Updated: 2026/05/06 14:09:41 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 프로그램의 진입점 (Entry Point)
 * @param argc 인자 개수
 * @param argv 인자 문자열 배열
 * @return 프로그램 종료 코드 (0: 성공, 1: 에러)
 */
int	main(int argc, char **argv)
{
	t_game	game;

	// 게임 구조체 초기화 (쓰레기값 참조 방지를 위해 가장 먼저 실행)
	ft_memset(&game, 0, sizeof(t_game));
	game.map.floor_color = -1;
	game.map.ceil_color = -1;
	// 인자가 2개가 아니면 사용법 출력 후 종료
	if (argc != 2)
		return (return_main_error(NULL, ERR_ARG));
	// 파일 확장자가 .cub인지 확인
	if (!check_extension(argv[1], ".cub"))
		return (return_main_error(NULL, ERR_EXT));
	// 맵 파일 파싱 및 유효성 검사
	if (parse_map(argv[1], &game) == -1)
		return (return_main_error(&game, ERR_NONE));
	if (init_game(&game) == -1)
		return (return_main_error(&game, ERR_NONE));
	// 텍스처 이미지 로드
	if (load_textures(&game) == -1)
		return (return_main_error(&game, ERR_NONE));
	// 게임 루프 시작 (이벤트 처리 및 렌더링)
	start_game_loop(&game);
	return (0);
}
