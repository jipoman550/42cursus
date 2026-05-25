/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 09:11:56 by sisung            #+#    #+#             */
/*   Updated: 2026/05/05 14:38:01 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 에러 코드(enum)에 대응하는 상세 에러 메시지를 반환합니다.
 * @param code 발생한 에러의 열거형 코드
 * @return 매핑된 에러 문자열 (상수)
 */
/*
static const char	*get_error_message(t_error code)
{
	static const char	*msgs[] = {
		"",
		"Memory allocation failed (malloc)",
		"Invalid arguments. Usage: ./cub3D [map.cub]",
		"Invalid file extension. Must be .cub or .xpm",
		"Failed to open file",
		"Duplicate texture or color configuration",
		"Invalid line configuration: Too many arguments",
		"Unknown identifier found in file",
		"Invalid texture path or missing file",
		"Invalid RGB color format (must be 0~255)",
		"Failed to initialize MLX",
		"Failed to load textures",
		"Map is separated by empty lines",
		"Invalid character in map",
		"No player position found or multiple players",
		"Map is not closed/surrounded by walls"
	};

	return (msgs[code]);
}
*/

/**
 * @brief 파일 입출력 및 설정(Config) 관련 에러 메시지를 반환합니다.
 * @param code 발생한 에러의 열거형 코드
 * @return 매핑된 에러 문자열 (상수)
 */
static const char	*get_config_error_msg(t_error code)
{
	if (code == ERR_MALLOC)
		return ("Memory allocation failed (malloc)");
	if (code == ERR_ARG)
		return ("Invalid arguments. Usage: ./cub3D [map.cub]");
	if (code == ERR_EXT)
		return ("Invalid file extension. Must be .cub or .xpm");
	if (code == ERR_FILE_OPEN)
		return ("Failed to open file");
	if (code == ERR_DUP_CONFIG)
		return ("Duplicate texture or color configuration");
	if (code == ERR_MISS_CONFIG)
		return ("Missing texture or color configuration");
	if (code == ERR_INV_ARGS)
		return ("Invalid line configuration: Too many arguments");
	if (code == ERR_INV_ID)
		return ("Unknown identifier found in file");
	if (code == ERR_INV_TEX)
		return ("Invalid texture path or missing file");
	return (NULL);
}

/**
 * @brief 맵 데이터, 색상 및 MLX 그래픽 관련 에러 메시지를 반환합니다.
 * @param code 발생한 에러의 열거형 코드
 * @return 매핑된 에러 문자열 (상수)
 */
static const char	*get_map_error_msg(t_error code)
{
	if (code == ERR_INV_COLOR)
		return ("Invalid RGB color format (must be 0~255)");
	if (code == ERR_MLX_INIT)
		return ("Failed to initialize MLX connection");
	if (code == ERR_MLX_WIN)
		return ("Failed to create MLX window");
	if (code == ERR_MLX_IMG)
		return ("Failed to create MLX image buffer");
	if (code == ERR_MLX_TEX)
		return ("Failed to load textures");
	if (code == ERR_MAP_GAP)
		return ("Map is separated by empty lines");
	if (code == ERR_MAP_CHAR)
		return ("Invalid character in map");
	if (code == ERR_PLAYER)
		return ("No player position found or multiple players");
	if (code == ERR_WALL)
		return ("Map is not closed/surrounded by walls");
	return (NULL);
}

/**
 * @brief 에러 코드에 해당하는 문자열을 반환합니다. (Norminette 준수)
 * @param code 발생한 에러 열거형 코드
 * @return 상수 문자열 포인터
 */
/*static const char	*get_error_msg(t_error code)
{
	const char	*msg;

	msg = get_config_error_msg(code);
	if (msg != NULL)
	{
		return (msg);
	}
	msg = get_map_error_msg(code);
	if (msg != NULL)
	{
		return (msg);
	}
	return ("Unknown error");
}*/

/**
 * @brief "Error\n"과 상세 메시지를 출력하고, 상위 함수로 에러(-1)를 전파합니다.
 * @details 분리되어 있던 메시지 매핑 로직을 병합하여 함수 개수(Norm)를 최적화했습니다.
 * @param code 출력할 에러 열거형 코드
 * @return 항상 -1을 반환
 */
int	print_error_and_return(t_error code)
{
	const char	*msg;

	msg = get_config_error_msg(code);
	if (msg == NULL)
	{
		msg = get_map_error_msg(code);
	}
	if (msg == NULL)
	{
		msg = "Unknown error";
	}
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (-1);
}

/**
 * @brief 파서에서 사용하는 로컬 변수 해제 및 에러 출력 헬퍼 함수
 */
int	free_parse_locals(char **tokens, char *str1, char *str2, t_error code)
{
	if (tokens != NULL)
	{
		free_split(tokens);
	}
	if (str1 != NULL)
	{
		free(str1);
	}
	if (str2 != NULL)
	{
		free(str2);
	}
	/* 에러 코드가 ERR_NONE이 아닐 때만 출력 */
	if (code != ERR_NONE)
	{
		return (print_error_and_return(code));
	}
	return (-1);
}

/**
 * @brief main 함수 전용: 에러 출력, 메모리 덤프 후 운영체제에 1을 반환합니다.
 * @param game 해제할 게임 구조체 (초기화 전이면 NULL 전달)
 * @param code 출력할 에러 코드 (ERR_NONE이면 출력 생략)
 * @return 항상 1 반환 (비정상 종료 코드)
 */
int	return_main_error(t_game *game, t_error code)
{
	if (code != ERR_NONE)
	{
		print_error_and_return(code);
	}
	if (game != NULL)
	{
		free_game(game);
	}
	return (1);
}
