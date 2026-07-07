#include "life.h"

int count_nb(char *b, int w, int h, int x, int y)
{
	int cnt = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0) continue ;

			int nx = x + j;
			int ny = y + i;

			if (nx >= 0 && nx < w && ny >= 0 && ny < h && b[ny * w + nx]) cnt++;
		}
	}
	return (cnt);
}

int main(int argc, char **argv)
{
	if (argc != 4) return (1);

	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int it = atoi(argv[3]);

	if (w <= 0 || h <= 0 || it < 0) return (1);

	char *b = calloc(w * h, 1);
	char *nb = calloc(w * h, 1);
	if (!b || !nb)
	{
		free(b); free(nb);
		return (1);
	}

	int px = 0, py = 0, draw = 0;
	char cmd;

	while (read(0, &cmd, 1) > 0)
	{
		if (cmd == 'w') py--;
		else if (cmd == 'a') px--;
		else if (cmd == 's') py++;
		else if (cmd == 'd') px++;
		else if (cmd == 'x') draw = !draw;

		if (px < 0) px = 0;
		if (px >= w) px = w - 1;
		if (px < 0) py = 0;
		if (py >= h) py = h - 1;

		if (draw) b[py * w + px] = 1;
	}

	for (int i = 0; i < it; i++)
	{
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				int n = count_nb(b, w, h, x, y);
				int alive = b[y * w + x];

				if (alive && (n < 2 || n > 3)) nb[y * w + x] = 0;
				else if (!alive && n == 3) nb[y * w + x] = 1;
				else nb[y * w + x] = alive;
			}
		}
		char *t = b;
		b = nb;
		nb = t;
	}

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			putchar(b[y * w + x] ? '0' : ' ');
		}
		putchar('\n');
	}

	free(b);
	free(nb);
	return (0);
}