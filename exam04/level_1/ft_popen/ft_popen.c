#include <stdlib.h>
#include <unistd.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	int fds[2];

	/* * 1단계: 인자 검사 및 파이프 생성
	 * - 모드가 'r' 또는 'w'가 아니면 즉시 에러 리턴.
	 * - 부모와 자식이 통신할 통로(pipe)를 먼저 만든다.
	 */
	if (type != 'r' && type != 'w')
		return (-1);
	if (pipe(fds) == -1)
		return (-1);

	/* * 2단계: 프로세스 복제 (fork)
	 * - 실행할 명령어(자식)와 이를 제어할 나(부모)로 나눈다.
	 * - 실패 시 생성했던 파이프를 모두 닫고 탈출한다.
	 */
	int pid = fork();
	if (pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}

	/* * 3단계: [자식 프로세스] 표준 스트림 교체
	 * - 'r'(읽기 모드): 내 출력(STDOUT)을 파이프 입구(fds[1])로 보낸다.
	 * - 'w'(쓰기 모드): 내 입력(STDIN)을 파이프 출구(fds[0])에서 받는다.
	 * - 연결이 끝난 파이프 원본들은 모두 닫는다.
	 */
	if (pid == 0)
	{
		if (type == 'r')
			dup2(fds[1], STDOUT_FILENO);
		else
			dup2(fds[0], STDIN_FILENO);

		close(fds[0]);
		close(fds[1]);

		/* * 4단계: [자식 프로세스] 명령어 실행
		 * - 새로운 프로그램으로 완전히 대체한다.
		 * - 만약 실행에 실패하면 즉시 종료(exit)하여 좀비를 방지한다.
		 */
		execvp(file, argv);
		exit(EXIT_FAILURE);
	}

	/* * 5단계: [부모 프로세스] 통신용 FD 리턴
	 * - 자식이 쓰기용(fds[1])을 쓰면, 부모는 읽기용(fds[0])만 남기고 닫은 뒤 리턴.
	 * - 자식이 읽기용(fds[0])을 쓰면, 부모는 쓰기용(fds[1])만 남기고 닫은 뒤 리턴.
	 */
	else
	{
		if (type == 'r')
		{
			close(fds[1]);
			return (fds[0]);
		}
		else
		{
			close(fds[0]);
			return (fds[1]);
		}
	}
}