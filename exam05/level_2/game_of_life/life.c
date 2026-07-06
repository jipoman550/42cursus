#include "life.h"

/**
 * @brief 특정 셀 주변의 살아있는 이웃 세포 수를 계산합니다.
 * @param b 게임 보드(1차원 배열 형태).
 * @param w 보드의 너비.
 * @param h 보드의 높이.
 * @param x 대상 셀의 x 좌표.
 * @param y 대상 셀의 y 좌표.
 * @return 살아있는 이웃 세포의 수를 반환합니다.
 */
int count_nb(char *b, int w, int h, int x, int y) {
	int cnt = 0; // 이웃 수를 저장할 변수

	// 대상 셀을 중심으로 3x3 격자를 순회합니다 (i: y 오프셋, j: x 오프셋).
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			// 대상 셀 자체는 계산에서 제외합니다.
			if (i == 0 && j == 0) continue;

			// 이웃 셀의 좌표를 계산합니다.
			int nx = x + j, ny = y + i;

			// 이웃 셀이 보드 경계 내에 있고 살아있는 상태인지 확인합니다.
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && b[ny * w + nx])
				cnt++; // 살아있다면 카운트를 증가시킵니다.
		}
	}
	return cnt; // 최종 이웃 수를 반환합니다.
}

/**
 * @brief 콘웨이의 생명 게임(Conway's Game of Life)을 시뮬레이션하는 메인 함수입니다.
 * @param argc 커맨드 라인 인자의 개수.
 * @param argv 커맨드 라인 인자 배열. argv[1]: 너비, argv[2]: 높이, argv[3]: 반복 횟수.
 * @return 정상 종료 시 0, 오류 발생 시 1을 반환합니다.
 */
int main(int argc, char **argv) {
	// 프로그램 실행 시 필요한 인자(너비, 높이, 반복 횟수)가 3개가 아니면 오류 처리합니다.
	if (argc != 4) return 1;

	// 커맨드 라인 인자를 정수로 변환하여 너비(w), 높이(h), 반복 횟수(it)를 설정합니다.
	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int it = atoi(argv[3]);

	// 너비, 높이가 0 이하이거나 반복 횟수가 0 미만이면 유효하지 않은 값이므로 오류 처리합니다.
	if (w <= 0 || h <= 0 || it < 0) return 1;

	// 현재 세대 보드(b)와 다음 세대 보드(nb)를 위한 메모리를 할당합니다.
	// calloc은 메모리를 0으로 초기화하므로 모든 셀이 '죽은' 상태로 시작됩니다.
	char *b = calloc(w * h, 1);
	char *nb = calloc(w * h, 1);
	// 메모리 할당에 실패하면 할당된 메모리를 해제하고 오류를 반환합니다.
	if (!b || !nb) {
		free(b); free(nb); // free(NULL)은 안전하므로 이렇게 작성해도 문제 없습니다.
		return 1;
	}

	// 1. 초기 보드 상태 설정
	// 표준 입력(stdin)으로부터 문자를 읽어와 초기 패턴을 그립니다.
	int px = 0, py = 0, draw = 0; // 커서 위치(px, py)와 그리기 모드(draw) 변수
	char cmd;

	// 표준 입력에서 1바이트씩 읽어옵니다. 파일의 끝(EOF)에 도달하면 루프가 종료됩니다.
	while (read(0, &cmd, 1) > 0) {
		// 입력된 명령어에 따라 커서 위치를 이동합니다.
		if (cmd == 'w') py--;       // 위로 이동
		else if (cmd == 'a') px--;  // 왼쪽으로 이동
		else if (cmd == 's') py++;  // 아래로 이동
		else if (cmd == 'd') px++;  // 오른쪽으로 이동
		else if (cmd == 'x') draw = !draw; // 그리기 모드를 토글합니다.

		// 커서가 보드 경계를 벗어나지 않도록 처리합니다.
		if (px < 0) px = 0;
		if (px >= w) px = w - 1;
		if (py < 0) py = 0;
		if (py >= h) py = h - 1;

		// 그리기 모드가 활성화된 경우, 현재 커서 위치의 셀을 '살아있는' 상태(1)로 만듭니다.
		if (draw) b[py * w + px] = 1;
	}

	// 2. 생명 게임 시뮬레이션
	// 지정된 반복 횟수(it)만큼 세대를 진행합니다.
	for (int i = 0; i < it; i++) {
		// 보드의 모든 셀을 순회합니다.
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				// 현재 셀의 살아있는 이웃 수를 계산합니다.
				int n = count_nb(b, w, h, x, y);
				// 현재 셀의 상태를 가져옵니다 (1: 살아있음, 0: 죽음).
				int alive = b[y * w + x];

				// 생명 게임의 규칙을 적용하여 다음 세대(nb)의 상태를 결정합니다.
				if (alive && (n < 2 || n > 3)) nb[y * w + x] = 0; // 1. 과소 또는 과밀 상태의 살아있는 셀은 죽습니다.
				else if (!alive && n == 3) nb[y * w + x] = 1;      // 2. 이웃이 3개인 죽은 셀은 살아납니다 (탄생).
				else nb[y * w + x] = alive;                        // 3. 그 외의 경우는 현재 상태를 유지합니다.
			}
		}
		// 포인터 스왑: 다음 세대를 현재 세대로 만듭니다.
		// 메모리 복사(memcpy)보다 훨씬 효율적입니다.
		char *t = b; b = nb; nb = t;
	}

	// 3. 최종 보드 상태 출력
	// 시뮬레이션이 끝난 후의 최종 보드(b)를 화면에 출력합니다.
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			// 살아있는 셀은 'O', 죽은 셀은 ' ' 문자를 출력합니다.
			putchar(b[y * w + x] ? 'O' : ' ');
		}
		// 각 행의 끝에서 줄바꿈 문자를 출력합니다.
		putchar('\n');
	}

	// 할당했던 메모리를 해제합니다.
	free(b);
	free(nb);
	return 0; // 프로그램 정상 종료
}