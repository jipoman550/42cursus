#define _GNU_SOURCE
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define BUFFER_SIZE 2

int perror_and_free(char *stash, char *stars)
{
    perror("Error");
    free(stash);
    free(stars);
    return 1;
}

int main(int argc, char **argv)
{
    /* 1) 인자 검사: 인자가 정확히 하나, 빈 문자열이면 실패 */
	if (argc != 2 || argv[1][0] == '\0')
		return 1;

	char buf[BUFFER_SIZE];
	char *stash = NULL; // 누적 버퍼 (이전 read() 잔여분 포함)
	size_t stash_len = 0;
	ssize_t r;
	char *pattern = argv[1];
	size_t pat_len = strlen(pattern);

	/* 패턴 길이 안전성 (문제에서 빈 패턴은 이미 막았으므로 pat_len >= 1) */
	/* 별문자(stars)를 한 번만 만들어 두고 재사용하면 출력이 조금 효율적입니다. */
	char *stars = malloc(pat_len);
	if (!stars)
	{
		perror("Error");
		return 1;
	}
	// memset(stars, '*', pat_len);
	for (size_t i = 0; i < pat_len; i++)
        stars[i] = '*';

    /*
	 * 2) read 루프
	 * - stdin에서 읽을 때마다 stash에 붙인다.
	 * - 붙인 뒤 memmem으로 stash에서 패턴을 반복적으로 찾고 처리한다.
	 * - 패턴을 모두 처리한 다음, '다음 read에서 이어질 수 있는 최대 길이' (pat_len - 1) 만큼만 stash에 남겨둔다.
	 */
	while ((r = read(STDIN_FILENO, buf, BUFFER_SIZE)) > 0)
	{
		/* stash를 확장해서 새로 읽어온 데이터 붙이기 */
		char *tmp = realloc(stash, stash_len + r);
		if (!tmp)
		{
			/* realloc 실패 시 에러 출력 후 정리 */
			perror_and_free(stash, stars);
		}

		stash = tmp;
		// memcpy(stash + stash_len, buf, r);
		memmove(stash + stash_len, buf, r);
		stash_len += r;

    	/* 이제 stash 안에서 패턴을 찾아 처리한다. offset은 처리 진행 위치 */
		size_t offset = 0;
		char *pos;

		/* memmem으로 현재 stash의 (offset부터 끝까지)에서 패턴을 찾는다 */
		while ((pos = memmem(stash + offset, stash_len - offset, pattern, pat_len)))
		{
			size_t prefix_len = pos - (stash + offset); /* 매치 전까지 길이 */

			/* 매치 전의 일반 텍스트는 그대로 출력 */
			if (prefix_len > 0)
			{
				if (write(STDOUT_FILENO, stash + offset, prefix_len) == -1)
					perror_and_free(stash, stars);
			}

			/* 패턴 부분은 '*'로 치환하여 출력 (한 번에 쓰기) */
			if (write(STDOUT_FILENO, stars, pat_len) == -1)
				perror_and_free(stash, stars);


			/* offset를 패턴 바로 다음 위치로 옮긴다 */
			offset += prefix_len + pat_len;
			/* 다음 루프에서 memmem은 (offset부터) 검색을 계속한다. */
		}

		/*
		* 이제 stash에서 offset 뒤에 남아 있는 데이터 중에서
		* "지금 출력해도 안전한 부분"은 즉시 출력하고,
		* "다음 read에서 이어질 수 있는 부분"은 남겨둔다.
		*
		* 안전하게 남겨둘 길이는 pat_len - 1 입니다.
		* (왜냐하면 패턴이 pat_len 길이이므로, 그보다 작은 접두부는 다음 읽기와 합쳐서 패턴이 될 수 있음)
		*/
		size_t keep = (pat_len > 0) ? pat_len - 1 : 0;

		if (stash_len > offset)
		{
			if (stash_len - offset > keep)
			{
				/* 지금 출력 가능한 길이 (= 전체 남은 길이 - keep) */
				size_t write_len = stash_len - offset - keep;
				if (write(STDOUT_FILENO, stash + offset, write_len) == -1)
					perror_and_free(stash, stars);

				/* tail(keep 바이트)을 버퍼 앞쪽으로 옮긴다 (다음 read에 대비) */
				memmove(stash, stash + offset + write_len, keep);
				stash_len = keep;
			}
			else
			{
				/* 남은 데이터 길이가 keep보다 작거나 같음 -> 아무 것도 출력하지 않고 그대로 보관 */
				memmove(stash, stash + offset, stash_len - offset);
				stash_len -= offset;
			}
		}
		else
		{
			/* 모든 바이트가 처리(또는 출력)되어 stash가 비게 되는 경우 */
			stash_len = 0;
		}
	} /* end read loop */

    /* read에서 에러가 났는지 확인 */
	if (r < 0)
		perror_and_free(stash, stars);


	/* EOF에 도달했을 때 stash에 남아있는 데이터는 더 이상 이어질 입력이 없으므로 모두 출력 */
	if (stash_len > 0)
	{
		if (write(STDOUT_FILENO, stash, stash_len) == -1)
		    perror_and_free(stash, stars);
	}

	free(stash);
	free(stars);
	return 0;
}
