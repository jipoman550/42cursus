#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h> // perror 때문에 추가

#define BUFFER_SIZE 2 // 테스트를 위해 작은 버퍼 크기로 설정

// 메모리 해제 및 에러 메시지 출력을 위한 헬퍼 함수
int perror_and_free(char *stash, char *stars)
{
	// 에러 메시지는 "Error: " + errno 메시지 형식으로 stderr에 출력됨
	perror("Error");
	// NULL을 free해도 안전하므로, stash가 NULL이더라도 문제 없음
	free(stash);
	free(stars);
	return 1;
}

int main(int argc, char *argv[])
{
	// 1. 인자 검사: 인자가 1개만 와야 하며, 빈 문자열이면 안 됨.
	if (argc != 2 || argv[1][0] == '\0')
		return 1;

	char buf[BUFFER_SIZE];
	char *stash = NULL; // 입력 데이터를 누적할 동적 버퍼
	size_t stash_len = 0; // stash의 현재 길이
	char *pattern = argv[1];
	size_t pat_len = strlen(pattern);
	ssize_t r; // read()의 반환값

	// 2. 패턴 길이만큼의 '*' 문자열(stars)을 미리 준비
	char *stars = malloc(pat_len);
	if (!stars)
	{
		perror("Error");
		return 1;
	}
	for (size_t i = 0; i < pat_len; ++i)
		stars[i] = '*';

	// 3. read를 반복하며 데이터를 stash에 누적하고 처리
	while ((r = read(STDIN_FILENO, buf, BUFFER_SIZE)) > 0)
	{
		// a. stash 확장 (realloc)
		char *tmp = realloc(stash, stash_len + r);
		if (!tmp)
			return perror_and_free(stash, stars); // 에러 발생 시 헬퍼 함수 호출

		stash = tmp;
		// b. 새 데이터 추가 (memmove)
		memmove(stash + stash_len, buf, r);
		stash_len += r;

		// c. 패턴 찾기 및 출력 (memmem 반복)
		size_t offset = 0; // 현재 stash에서 처리한 데이터의 시작점
		char *pos;
		while ((pos = memmem(stash + offset, stash_len - offset, pattern, pat_len)))
		{
			// i. 패턴 직전까지의 접두사 길이
			size_t prefix_len = pos - (stash + offset);

			// ii. 접두사 출력
			if (prefix_len > 0)
			{
				if (write(STDOUT_FILENO, stash + offset, prefix_len) == -1)
					return perror_and_free(stash, stars);
			}
			// iii. '*' 출력
			if (write(STDOUT_FILENO, stars, pat_len) == -1)
				return perror_and_free(stash, stars);

			// iv. offset 업데이트: 다음 검색은 패턴이 끝난 지점부터 시작
			offset += prefix_len + pat_len;
		}

		// d. Stash Cleanup (가장 까다로운 부분: 다음 read에 걸쳐 패턴이 완성될 수 있는 부분만 남기기)
		size_t keep = (pat_len > 0) ? pat_len - 1 : 0; // 패턴 길이-1 만큼만 남겨야 안전함

		if (stash_len > offset) // 처리되지 않은 잔여 데이터가 있을 때
		{
			size_t remaining = stash_len - offset; // 현재 남은 데이터의 실제 길이

			if (remaining > keep) // 남은 데이터가 keep보다 길다면 (안전하게 출력 가능한 부분이 있음)
			{
				// 안전하게 출력할 길이 = remaining - keep
				size_t write_len = remaining - keep;
				if (write(STDOUT_FILENO, stash + offset, write_len) == -1)
					return perror_and_free(stash, stars);

				// 남겨야 할 keep 부분(remaining - write_len)을 stash 맨 앞으로 이동
				memmove(stash, stash + offset + write_len, keep);
				stash_len = keep;
			}
			else // 남은 데이터가 keep보다 짧거나 같다면 (모두 남겨둬야 함)
			{
				// 남은 데이터를 stash 맨 앞으로 이동
				memmove(stash, stash + offset, remaining);
				stash_len = remaining;
			}
		}
		else // stash_len == offset, 모두 처리되었으므로 stash를 비움
		{
			stash_len = 0;
		}
	}

	// 4. read 루프 후 잔여 에러 및 데이터 처리
	if (r < 0) // read()가 실패했을 경우
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
