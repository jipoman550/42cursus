/* ************************************************************************** */
/*                                                                            */
/*   test_parsing.c - cub3D 파싱 모듈 자동 테스트                        */
/*                                                                            */
/*   make test 로 실행하세요                                                */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <string.h>

/* Color codes for terminal output */
#define CLR_GREEN  "\033[1;32m"
#define CLR_RED    "\033[1;31m"
#define CLR_YELLOW "\033[1;33m"
#define CLR_CYAN   "\033[1;36m"
#define CLR_RESET  "\033[0m"

static int	g_total = 0;
static int	g_pass = 0;
static int	g_fail = 0;

/**
 * @brief game 구조체 멤버를 0으로 초기화하는 헬퍼
 */
static void	init_game(t_game *game)
{
	memset(game, 0, sizeof(t_game));
	game->map.floor_color = -1;
	game->map.ceil_color = -1;
}

/**
 * @brief game 구조체의 동적 메모리를 해제하는 헬퍼
 */
static void	free_game(t_game *game)
{
	int	i;

	if (game->map.no_path) free(game->map.no_path);
	if (game->map.so_path) free(game->map.so_path);
	if (game->map.we_path) free(game->map.we_path);
	if (game->map.ea_path) free(game->map.ea_path);
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			if (game->map.grid[i])
				free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
}

/* ========================================================================== */
/*  유효한 맵 테스트 (parse_map이 0을 반환해야 함)                         */
/* ========================================================================== */

/**
 * @brief 유효한 맵이 정상적으로 파싱되는지 검사
 * @param test_name 테스트 이름 (출력용)
 * @param file_path 테스트할 .cub 파일 경로
 */
static void	test_valid_map(const char *test_name, const char *file_path)
{
	t_game	game;
	int		ret;

	g_total++;
	init_game(&game);
	ret = parse_map(file_path, &game);
	if (ret == 0)
	{
		printf("  " CLR_GREEN "[PASS]" CLR_RESET " %s\n", test_name);
		g_pass++;
	}
	else
	{
		printf("  " CLR_RED "[FAIL]" CLR_RESET " %s (expected 0, got %d)\n",
			test_name, ret);
		g_fail++;
	}
	free_game(&game);
}

/**
 * @brief 유효하지 않은 맵에서 parse_map이 에러(-1)를 반환하는지 검사
 * @param test_name 테스트 이름 (출력용)
 * @param file_path 테스트할 .cub 파일 경로
 */
static void	test_invalid_map(const char *test_name, const char *file_path)
{
	t_game	game;
	int		ret;

	g_total++;
	init_game(&game);
	ret = parse_map(file_path, &game);
	if (ret == -1)
	{
		printf("  " CLR_GREEN "[PASS]" CLR_RESET " %s\n", test_name);
		g_pass++;
	}
	else
	{
		printf("  " CLR_RED "[FAIL]" CLR_RESET " %s (expected -1, got %d)\n",
			test_name, ret);
		g_fail++;
	}
	free_game(&game);
}

/**
 * @brief 유효한 맵에서 파싱된 데이터가 올바른지 상세 검증
 */
static void	test_valid_basic_details(void)
{
	t_game	game;
	int		ret;

	g_total++;
	init_game(&game);
	ret = parse_map("tests/maps/valid_basic.cub", &game);
	if (ret != 0)
	{
		printf("  " CLR_RED "[FAIL]" CLR_RESET
			" valid_basic details: parse_map failed (%d)\n", ret);
		g_fail++;
		free_game(&game);
		return ;
	}

	int	all_ok = 1;

	/* 텍스처 경로 확인 */
	if (!game.map.no_path || strcmp(game.map.no_path, "./textures/north.xpm") != 0)
	{ printf("    " CLR_RED "✗" CLR_RESET " NO path mismatch: [%s]\n", game.map.no_path); all_ok = 0; }
	if (!game.map.so_path || strcmp(game.map.so_path, "./textures/south.xpm") != 0)
	{ printf("    " CLR_RED "✗" CLR_RESET " SO path mismatch: [%s]\n", game.map.so_path); all_ok = 0; }
	if (!game.map.we_path || strcmp(game.map.we_path, "./textures/west.xpm") != 0)
	{ printf("    " CLR_RED "✗" CLR_RESET " WE path mismatch: [%s]\n", game.map.we_path); all_ok = 0; }
	if (!game.map.ea_path || strcmp(game.map.ea_path, "./textures/east.xpm") != 0)
	{ printf("    " CLR_RED "✗" CLR_RESET " EA path mismatch: [%s]\n", game.map.ea_path); all_ok = 0; }

	/* 색상 확인: F 220,100,0 => (220<<16)|(100<<8)|0 = 14443520 */
	int	expected_floor = (220 << 16) | (100 << 8) | 0;
	if (game.map.floor_color != expected_floor)
	{ printf("    " CLR_RED "✗" CLR_RESET " Floor color: expected %d, got %d\n", expected_floor, game.map.floor_color); all_ok = 0; }

	/* 색상 확인: C 225,30,0 => (225<<16)|(30<<8)|0 = 14745088 */
	int	expected_ceil = (225 << 16) | (30 << 8) | 0;
	if (game.map.ceil_color != expected_ceil)
	{ printf("    " CLR_RED "✗" CLR_RESET " Ceil color: expected %d, got %d\n", expected_ceil, game.map.ceil_color); all_ok = 0; }

	/* 맵 크기 확인 */
	if (game.map.height != 5)
	{ printf("    " CLR_RED "✗" CLR_RESET " Height: expected 5, got %d\n", game.map.height); all_ok = 0; }
	if (game.map.width != 6)
	{ printf("    " CLR_RED "✗" CLR_RESET " Width: expected 6, got %d\n", game.map.width); all_ok = 0; }

	/* 플레이어 위치/방향 확인 (N: row=3, col=4 => pos_x=4.5, pos_y=3.5) */
	if (game.player.pos_x < 4.4 || game.player.pos_x > 4.6)
	{ printf("    " CLR_RED "✗" CLR_RESET " Player pos_x: expected ~4.5, got %f\n", game.player.pos_x); all_ok = 0; }
	if (game.player.pos_y < 3.4 || game.player.pos_y > 3.6)
	{ printf("    " CLR_RED "✗" CLR_RESET " Player pos_y: expected ~3.5, got %f\n", game.player.pos_y); all_ok = 0; }

	/* N 방향: dir(0,-1), plane(0.66,0) */
	if (game.player.dir_y != -1.0 || game.player.dir_x != 0.0)
	{ printf("    " CLR_RED "✗" CLR_RESET " Player dir: expected (0,-1), got (%f,%f)\n", game.player.dir_x, game.player.dir_y); all_ok = 0; }

	if (all_ok)
	{
		printf("  " CLR_GREEN "[PASS]" CLR_RESET " valid_basic 상세 데이터 검증\n");
		g_pass++;
	}
	else
	{
		printf("  " CLR_RED "[FAIL]" CLR_RESET " valid_basic 상세 데이터 검증 (위 세부 항목 참조)\n");
		g_fail++;
	}

	free_game(&game);
}

/**
 * @brief 존재하지 않는 파일에 대한 에러 처리 검사
 */
static void	test_nonexistent_file(void)
{
	t_game	game;
	int		ret;

	g_total++;
	init_game(&game);
	ret = parse_map("tests/maps/this_file_does_not_exist.cub", &game);
	if (ret == -1)
	{
		printf("  " CLR_GREEN "[PASS]" CLR_RESET " 존재하지 않는 파일 처리\n");
		g_pass++;
	}
	else
	{
		printf("  " CLR_RED "[FAIL]" CLR_RESET
			" 존재하지 않는 파일 처리 (expected -1, got %d)\n", ret);
		g_fail++;
	}
	free_game(&game);
}

/* ========================================================================== */
/*                               main                                         */
/* ========================================================================== */

int	main(void)
{
	printf("\n");
	printf(CLR_CYAN "╔══════════════════════════════════════════════════════╗\n");
	printf("║         cub3D 파싱 테스트 (Step 2)                  ║\n");
	printf("╚══════════════════════════════════════════════════════╝\n" CLR_RESET);
	printf("\n");

	/* ---- Section 1: 유효한 맵 테스트 ---- */
	printf(CLR_YELLOW "── 유효한 맵 (parse_map → 0 기대) ──\n" CLR_RESET);
	test_valid_map("valid_basic.cub   : 기본 맵",
		"tests/maps/valid_basic.cub");
	test_valid_map("valid_all_dirs.cub: 플레이어 S방향",
		"tests/maps/valid_all_dirs.cub");
	test_valid_map("valid_spaces.cub  : 넓은 맵, E방향",
		"tests/maps/valid_spaces.cub");
	test_valid_map("valid_irregular.cub: 불규칙 맵, W방향",
		"tests/maps/valid_irregular.cub");
	printf("\n");

	/* ---- Section 2: 상세 데이터 검증 ---- */
	printf(CLR_YELLOW "── 상세 데이터 검증 ──\n" CLR_RESET);
	test_valid_basic_details();
	printf("\n");

	/* ---- Section 3: 유효하지 않은 맵 테스트 ---- */
	printf(CLR_YELLOW "── 유효하지 않은 맵 (parse_map → -1 기대) ──\n" CLR_RESET);
	test_invalid_map("open_wall.cub     : 벽이 열린 맵",
		"tests/maps/invalid_open_wall.cub");
	test_invalid_map("no_player.cub     : 플레이어 없음",
		"tests/maps/invalid_no_player.cub");
	test_invalid_map("two_players.cub   : 플레이어 2명",
		"tests/maps/invalid_two_players.cub");
	test_invalid_map("bad_char.cub      : 유효하지 않은 문자",
		"tests/maps/invalid_bad_char.cub");
	test_invalid_map("missing_texture   : 텍스처 누락 (EA)",
		"tests/maps/invalid_missing_texture.cub");
	test_invalid_map("bad_color.cub     : RGB 범위 초과 (256)",
		"tests/maps/invalid_bad_color.cub");
	test_invalid_map("space_leak.cub    : 공백이 내부로 침투",
		"tests/maps/invalid_space_leak.cub");
	test_nonexistent_file();
	printf("\n");

	/* ---- Summary ---- */
	printf(CLR_CYAN "══════════════════════════════════════════════════════\n" CLR_RESET);
	printf("  Total: %d  |  ", g_total);
	printf(CLR_GREEN "Pass: %d" CLR_RESET "  |  ", g_pass);
	if (g_fail > 0)
		printf(CLR_RED "Fail: %d" CLR_RESET, g_fail);
	else
		printf("Fail: %d", g_fail);
	printf("\n");
	printf(CLR_CYAN "══════════════════════════════════════════════════════\n" CLR_RESET);

	if (g_fail > 0)
	{
		printf(CLR_RED "\n  ❌ 일부 테스트가 실패했습니다!\n\n" CLR_RESET);
		return (1);
	}
	printf(CLR_GREEN "\n  ✅ 모든 테스트를 통과했습니다!\n\n" CLR_RESET);
	return (0);
}
