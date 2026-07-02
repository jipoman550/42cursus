#include "life.h"

// 허용 함수인 putchar 선언
int putchar(int c);

// 이웃 세는 함수는 재사용되므로 별도 분리 (변수명 최소화)
int count_nb(char *b, int w, int h, int x, int y) {
	int cnt = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			int nx = x + j, ny = y + i;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && b[ny * w + nx])
				cnt++;
		}
	}
	return cnt;
}

int main(int argc, char **argv) {
	if (argc != 4) return 1;

	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int it = atoi(argv[3]);

	if (w <= 0 || h <= 0 || it < 0) return 1;

	char *b = calloc(w * h, 1);
	char *nb = calloc(w * h, 1);
	if (!b || !nb) {
		free(b); free(nb);
		return 1;
	}

	// 1. 초기 보드 그리기
	int px = 0, py = 0, draw = 0;
	char cmd;

	while (read(0, &cmd, 1) > 0) {
		if (cmd == 'w') py--;
		else if (cmd == 'a') px--;
		else if (cmd == 's') py++;
		else if (cmd == 'd') px++;
		else if (cmd == 'x') draw = !draw;

		if (px < 0) px = 0;
		if (px >= w) px = w - 1;
		if (py < 0) py = 0;
		if (py >= h) py = h - 1;

		if (draw) b[py * w + px] = 1;
	}

	// 2. 생명 게임 시뮬레이션 (기존 오타 수정 완료)
	for (int i = 0; i < it; i++) {
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				int n = count_nb(b, w, h, x, y);
				int alive = b[y * w + x];

				if (alive && (n < 2 || n > 3)) nb[y * w + x] = 0;
				else if (!alive && n == 3) nb[y * w + x] = 1;
				else nb[y * w + x] = alive;
			}
		}
		char *t = b; b = nb; nb = t; // 포인터 스왑
	}

	// 3. 최종 출력 인라인화 (여기에 합침)
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			putchar(b[y * w + x] ? 'O' : ' ');
		}
		putchar('\n');
	}

	free(b);
	free(nb);
	return 0;
}