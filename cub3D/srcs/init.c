#include "cub3d.h"

/**
 * @brief 이미지 버퍼의 (x, y) 좌표에 색상을 기록
 * @param img 픽셀을 그릴 대상 이미지 구조체
 * @param x 픽셀의 x 좌표
 * @param y 픽셀의 y 좌표
 * @param color 기록할 색상 값 (TRGB)
 */
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	// 화면 범위를 벗어나는 좌표는 무시 (Segfault 방지)
	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	// 메모리 주소 계산: 시작 주소 + (y * 한 줄 길이) + (x * 픽셀 당 바이트 수)
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	// 계산된 주소에 색상 값 저장
	*(unsigned int *)dst = color;
}

/**
 * @brief ESC 키 또는 지원 키 입력 시 호출되는 콜백 (Step 1에서는 ESC만 처리)
 * @param keycode 입력된 키의 코드 값
 * @param game 게임 구조체 포인터
 * @return 이벤트 처리 결과 (0)
 */
static int	key_press_handler(int keycode, t_game *game)
{
	// ESC 키(65307)가 눌리면 게임 종료
	if (keycode == 65307)
		exit_game(game, 0);
	return (0);
}

/**
 * @brief 창 X 버튼 클릭 시 호출되는 콜백
 * @param game 게임 구조체 포인터
 * @return 이벤트 처리 결과 (0)
 */
static int	close_window_handler(t_game *game)
{
	// 창 닫기 버튼 클릭 시 게임 종료
	exit_game(game, 0);
	return (0);
}

/**
 * @brief MLX 세션, 윈도우, 이미지 버퍼를 초기화
 * @param game 초기화할 게임 구조체 포인터
 * @return 성공 시 0, 실패 시 -1 반환
 */
int	init_game(t_game *game)
{
	// MLX 라이브러리 연결 초기화
	game->mlx = mlx_init();
	if (!game->mlx)
		return (-1);
	// 윈도우 생성 (제목: cub3D)
	game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!game->win)
		return (-1);
	// 화면에 표시할 메인 이미지 버퍼 생성
	game->img.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	if (!game->img.img)
		return (-1);
	// 이미지 데이터의 메모리 주소 및 정보 가져오기
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	// 플레이어 이동 및 회전 속도 초기값 설정
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.03;
	return (0);
}

/**
 * @brief 4방향 텍스처 .xpm 파일을 로드
 * textures[0]=NO, [1]=SO, [2]=WE, [3]=EA
 * @param game 게임 구조체 포인터
 * @return 모든 텍스처 로드 성공 시 0, 하나라도 실패 시 -1
 */
int	load_textures(t_game *game)
{
	int	w;
	int	h;

	// 각 방향의 xpm 파일을 읽어 이미지로 변환
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx,
			game->map.no_path, &w, &h);
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx,
			game->map.so_path, &w, &h);
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx,
			game->map.we_path, &w, &h);
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx,
			game->map.ea_path, &w, &h);
	// 이미지 로드 실패 여부 확인
	if (!game->textures[0].img || !game->textures[1].img
		|| !game->textures[2].img || !game->textures[3].img)
	{
		write(2, "Error\nFailed to load textures\n", 30);
		return (-1);
	}
	// 로드된 텍스처 이미지의 데이터 주소 가져오기 (픽셀 접근용)
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img,
			&game->textures[0].bpp, &game->textures[0].line_len,
			&game->textures[0].endian);
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].img,
			&game->textures[1].bpp, &game->textures[1].line_len,
			&game->textures[1].endian);
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].img,
			&game->textures[2].bpp, &game->textures[2].line_len,
			&game->textures[2].endian);
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].img,
			&game->textures[3].bpp, &game->textures[3].line_len,
			&game->textures[3].endian);
	return (0);
}

/**
 * @brief 동적 할당된 모든 자원을 해제
 * @param game 해제할 게임 구조체 포인터
 */
void	free_game(t_game *game)
{
	int	i;

	// 맵 그리드(2차원 배열) 메모리 해제
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
	// 텍스처 파일 경로 문자열 해제
	if (game->map.no_path)
		free(game->map.no_path);
	if (game->map.so_path)
		free(game->map.so_path);
	if (game->map.we_path)
		free(game->map.we_path);
	if (game->map.ea_path)
		free(game->map.ea_path);
	// 로드된 텍스처 이미지 해제
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	// 메인 이미지 버퍼 해제
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	// 윈도우 파괴
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	// MLX 디스플레이 연결 해제 및 메모리 해제
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/**
 * @brief 게임 종료: 자원 해제 후 프로세스 종료
 * @param game 게임 구조체 포인터
 * @param exit_code 종료 코드
 */
void	exit_game(t_game *game, int exit_code)
{
	// 모든 자원 해제 후 종료
	free_game(game);
	exit(exit_code);
}

/**
 * @brief MLX 이벤트 훅을 등록하고 루프를 시작
 * @param game 게임 구조체 포인터
 */
void	start_game_loop(t_game *game)
{
	// 키 입력 이벤트(2) 훅 등록
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	// 창 닫기 버튼 이벤트(17) 훅 등록
	mlx_hook(game->win, 17, 0, close_window_handler, game);
	// MLX 메인 루프 시작 (이벤트 대기)
	mlx_loop(game->mlx);
}
