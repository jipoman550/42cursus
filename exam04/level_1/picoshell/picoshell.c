#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
	int i = 0;
	int pipe_fds[2];
	/* * [논리 1: 유산의 상속]
	 * 이전 자식이 남겨준 '읽기 끝'을 저장할 변수입니다.
	 * 첫 번째 명령어는 받을 유산이 없으므로 -1로 시작합니다.
	 */
	int prev_read_end = -1;

	while (cmds[i])
	{
		/* * [논리 2: 미래를 향한 통로 개설]
		 * 현재 명령어가 마지막이 아니라면, 다음 명령어에게 데이터를 줄 통로(Pipe)가 필요합니다.
		 * 자식을 낳기(fork) 전에 미리 길을 뚫어놓는 작업입니다.
		 */
		if (cmds[i + 1])
		{
			if (pipe(pipe_fds) == -1)
				return 1;
		}

		/* [논리 3: 개별 작업자 생성] */
		pid_t pid = fork();
		if (pid == -1)
		{
			if (prev_read_end != -1)
				close(prev_read_end);
			if (cmds[i + 1])
			{
				close(pipe_fds[0]);
				close(pipe_fds[1]);
			}
			return (1);
		}

		if (pid == 0)
		{
			/* --- 자식 프로세스 (실행 주자)의 논리 --- */

			/* * [논리 4: 과거와의 연결 - 입력 리다이렉션]
			 * 이전 명령어에서 온 데이터(유산)가 있다면,
			 * 나의 표준 입력(STDIN)을 그 입구(prev_read_end)로 교체합니다.
			 */
			if (prev_read_end != -1)
			{
				dup2(prev_read_end, STDIN_FILENO);
				close(prev_read_end); // 복사본을 만들었으니 원본은 닫습니다.
			}

			/* * [논리 5: 미래와의 연결 - 출력 리다이렉션]
			 * 뒤에 올 명령어가 있다면, 나의 표준 출력(STDOUT)을
			 * 아까 뚫어놓은 파이프의 입구(pipe_fds[1])로 교체합니다.
			 */
			if (cmds[i + 1])
			{
				close(pipe_fds[0]); // 자식은 파이프에서 읽지 않으므로 출구는 미리 닫습니다.
				dup2(pipe_fds[1], STDOUT_FILENO);
				close(pipe_fds[1]); // 복사본을 만들었으니 원본은 닫습니다.
			}

			/* * [논리 6: 변신 및 실행]
			 * 연결이 끝났으므로 실제 명령어로 갈아입습니다.
			 * 성공하면 아래 exit(1)까지 내려오지 않습니다.
			 */
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		else
		{
			/* --- 부모 프로세스 (조정자)의 논리 --- */

			/* * [논리 7: 쓸모없어진 유산 정리]
			 * 자식에게 성공적으로 넘겨준 '이전 파이프의 출구'는
			 * 부모 입장에서는 이제 필요 없으므로 닫아서 FD 누수를 막습니다.
			 */
			if (prev_read_end != -1)
				close(prev_read_end);

			/* * [논리 8: 다음 주자를 위한 바톤 터치]
			 * 이번에 만든 파이프의 입구(pipe_fds[1])는 자식이 썼으니 닫고,
			 * 출구(pipe_fds[0])는 다음 루프의 자식이 '입력'으로 쓸 수 있게 보관합니다.
			 */
			if (cmds[i + 1])
			{
				close(pipe_fds[1]);
				prev_read_end = pipe_fds[0];
			}
		}
		i++;
	}

	/* * [논리 9: 동기화 및 마무리]
	 * 모든 명령을 내렸으니, 모든 자식들이 완주(종료)할 때까지 기다립니다.
	 * wait()이 -1을 반환(더 이상 자식이 없음)할 때까지 루프를 돕니다.
	 */
	while (wait(NULL) > 0); // 궁금한게 이거 없으면 어떻게 되는지 원리를 보고 싶은데?
	return 0;
}