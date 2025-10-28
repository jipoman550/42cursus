#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

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
	// 1. 인자 검사: 인자가 1개만 와야함. 빈 문자열이면 안됨.
	if (argc != 2 || argv[1][0] == '\0')
		return 1;

	char buf[BUFFER_SIZE];
	char *stash = NULL;
	size_t stash_len = 0;
	char *pattern = argv[1];
	size_t pat_len = strlen(pattern);
	ssize_t r;

	// 2. 패턴 길이만큼의 '*'  문자열(stars)을 미리 준비
	char *stars = malloc(pat_len);
	if (!stars)
	{
		perror("Error");
		return 1;
	}
	for (size_t i = 0; i < pat_len; ++i)
		stars[i] = '*';

	// 3. read를 반복하며 데이터를 stash를 누적하고 처리
	while ((r = read(STDIN_FILENO, buf, BUFFER_SIZE)) > 0)
	{
		// a. stash 확장(realloc)
		char *tmp = realloc(stash, stash_len + r);
		if (!tmp)
			return (perror_and_free(stash, stars));
		stash = tmp;

		// b. 새 데이터 추가 (memmove)
		memmove(stash + stash_len, buf, r);
		stash_len += r;

		// c. 패턴 찾기 및 출력 (memmem 반복)
		size_t offset = 0;
		char *pos;
		while ((pos = memmem(stash + offset, stash_len - offset, pattern, pat_len)))
		{
			// 1) 패턴 직전까지의 접두사 길이
			size_t prefix_len = pos - (stash + offset);
			// 2) 접두사 출력
			if (prefix_len > 0)
			{
				if (write(STDOUT_FILENO, stash + offset, prefix_len) == -1)
					return perror_and_free(stash, stars);
			}
			// 3) '*' 출력
			if (write(STDOUT_FILENO, stars, pat_len) == -1)
				return perror_and_free(stash, stars);
			// 4) offset 업데이트 : 다음 검색은 패턴이 끝난 지점 부터 시작
			offset += prefix_len + pat_len;

		}

		// d. stash cleanup (다음 read에 걸쳐 패턴이 완성 될 수 있는 부분만 남기기)
		size_t keep = (pat_len > 0) ? pat_len - 1 : 0;
		// 1) 처리되지 않은 잔여 데이터가 있을 때
		if (stash_len > offset)
		{
			size_t remaining = stash_len - offset;
			// 남은 데이터가 keep 보다 길다면 (안전하게 출력 가능한 부분이 있음)
			if (remaining > keep)
			{
				size_t write_len = remaining - keep;
				if (write(STDOUT_FILENO, stash + offset, write_len) == -1)
					return perror_and_free(stash, stars);
				memmove(stash, stash + offset + write_len, keep);
				stash_len = keep;
			}
			// 남은 데이터가 kepp 보다 짧거나 같다면 (모두 남겨둬야 됨)
			else
			{
				memmove(stash, stash + offset, remaining);
				stash_len = remaining;
			}
		}
		// stash_len == offset, 모두 처리되었으므로 stash를 비움
		else
		{
			stash_len = 0;
		}
	}
	// 4. read 루프 후 잔여 에러 및 데이터 처리
	if (r < 0)
		return perror_and_free(stash, stars);

	// 5. stash에 남아있는 최종 잔여 데이터 출력 (마지막까지 패턴이 발견되지 않은 부분)
	if (stash_len > 0)
	{
		if (write(STDOUT_FILENO, stash, stash_len) == -1)
			return perror_and_free(stash, stars);
	}

	// 6. 메모리 해제 및 정상 종료
	free(stash);
	free(stars);
	return 0;
}