#include "cub3d.h"

/* Key codes for Linux (X11) */
# define KEY_W      119
# define KEY_A      97
# define KEY_S      115
# define KEY_D      100
# define KEY_LEFT   65361
# define KEY_RIGHT  65363
# define KEY_ESC    65307

/**
 * @brief 플레이어를 앞으로 전진시킨다 (W키)
 * 방향 벡터 방향으로 move_speed만큼 이동하되, 벽 충돌 체크를 수행
 * @param game 게임 구조체 포인터
 */
static void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	// 방향 벡터에 이동 속도를 곱하여 새 좌표 계산
	new_x = game->player.pos_x + game->player.dir_x
		* game->player.move_speed;
	new_y = game->player.pos_y + game->player.dir_y
		* game->player.move_speed;
	// X축 이동: 벽이 아닌 경우에만 위치 갱신
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	// Y축 이동: 벽이 아닌 경우에만 위치 갱신
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

/**
 * @brief 플레이어를 뒤로 후진시킨다 (S키)
 * 방향 벡터 반대 방향으로 move_speed만큼 이동
 * @param game 게임 구조체 포인터
 */
static void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	// 방향 벡터의 반대 방향으로 새 좌표 계산
	new_x = game->player.pos_x - game->player.dir_x
		* game->player.move_speed;
	new_y = game->player.pos_y - game->player.dir_y
		* game->player.move_speed;
	// X축 이동: 벽이 아닌 경우에만 위치 갱신
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	// Y축 이동: 벽이 아닌 경우에만 위치 갱신
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

/**
 * @brief 플레이어를 왼쪽으로 이동시킨다 (A키)
 * 카메라 평면 벡터의 반대 방향으로 이동 (왼쪽 스트레이프)
 * @param game 게임 구조체 포인터
 */
static void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	// 카메라 평면 벡터의 반대 방향으로 새 좌표 계산
	new_x = game->player.pos_x - game->player.plane_x
		* game->player.move_speed;
	new_y = game->player.pos_y - game->player.plane_y
		* game->player.move_speed;
	// X축 이동: 벽이 아닌 경우에만 위치 갱신
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	// Y축 이동: 벽이 아닌 경우에만 위치 갱신
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

/**
 * @brief 플레이어를 오른쪽으로 이동시킨다 (D키)
 * 카메라 평면 벡터 방향으로 이동 (오른쪽 스트레이프)
 * @param game 게임 구조체 포인터
 */
static void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	// 카메라 평면 벡터 방향으로 새 좌표 계산
	new_x = game->player.pos_x + game->player.plane_x
		* game->player.move_speed;
	new_y = game->player.pos_y + game->player.plane_y
		* game->player.move_speed;
	// X축 이동: 벽이 아닌 경우에만 위치 갱신
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	// Y축 이동: 벽이 아닌 경우에만 위치 갱신
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

/**
 * @brief 플레이어 시점을 왼쪽으로 회전시킨다 (← 화살표)
 * 2D 회전 행렬을 사용: [cos(a) -sin(a); sin(a) cos(a)]
 * 방향 벡터와 카메라 평면 벡터 모두 동일하게 회전
 * @param game 게임 구조체 포인터
 */
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	// 회전 각도에 대한 cos, sin 값 계산 (음수: 반시계 방향)
	cos_a = cos(-game->player.rot_speed);
	sin_a = sin(-game->player.rot_speed);
	// 방향 벡터 회전
	old_dir_x = game->player.dir_x;
	game->player.dir_x = old_dir_x * cos_a - game->player.dir_y * sin_a;
	game->player.dir_y = old_dir_x * sin_a + game->player.dir_y * cos_a;
	// 카메라 평면 벡터 회전 (방향 벡터와 동일한 각도로)
	old_plane_x = game->player.plane_x;
	game->player.plane_x = old_plane_x * cos_a - game->player.plane_y * sin_a;
	game->player.plane_y = old_plane_x * sin_a + game->player.plane_y * cos_a;
}

/**
 * @brief 플레이어 시점을 오른쪽으로 회전시킨다 (→ 화살표)
 * 2D 회전 행렬을 사용: [cos(a) -sin(a); sin(a) cos(a)]
 * 방향 벡터와 카메라 평면 벡터 모두 동일하게 회전
 * @param game 게임 구조체 포인터
 */
void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	// 회전 각도에 대한 cos, sin 값 계산 (양수: 시계 방향)
	cos_a = cos(game->player.rot_speed);
	sin_a = sin(game->player.rot_speed);
	// 방향 벡터 회전
	old_dir_x = game->player.dir_x;
	game->player.dir_x = old_dir_x * cos_a - game->player.dir_y * sin_a;
	game->player.dir_y = old_dir_x * sin_a + game->player.dir_y * cos_a;
	// 카메라 평면 벡터 회전 (방향 벡터와 동일한 각도로)
	old_plane_x = game->player.plane_x;
	game->player.plane_x = old_plane_x * cos_a - game->player.plane_y * sin_a;
	game->player.plane_y = old_plane_x * sin_a + game->player.plane_y * cos_a;
}

/**
 * @brief 키 입력 이벤트 콜백 함수
 * mlx_hook으로 등록되어 키가 눌릴 때마다 호출됨
 * WASD: 이동, ←→: 회전, ESC: 종료
 * @param keycode 입력된 키의 X11 코드 값
 * @param game 게임 구조체 포인터
 * @return 이벤트 처리 결과 (0)
 */
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game, 0);
	else if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == KEY_LEFT)
		rotate_left(game);
	else if (keycode == KEY_RIGHT)
		rotate_right(game);
	return (0);
}

/**
 * @brief 창 X 버튼 클릭 시 호출되는 콜백
 * DestroyNotify(17) 이벤트에 훅으로 등록됨
 * @param game 게임 구조체 포인터
 * @return 이벤트 처리 결과 (0)
 */
int	close_window(t_game *game)
{
	exit_game(game, 0);
	return (0);
}
