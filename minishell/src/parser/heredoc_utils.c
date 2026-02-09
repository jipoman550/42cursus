/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:46:59 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:38 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** 함수 역할: 두 문자열을 비교.
** @param s1 첫 번째 문자열.
** @param s2 두 번째 문자열.
** @return 차이값 (같으면 0).
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && s1[i]) // 문자가 같고 끝이 아닐 때까지
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]); // 차이 반환
}

/*
** 함수 역할: 고유한 임시 파일 이름 생성 (.heredoc_숫자).
** @param i 고유 번호.
** @return 생성된 파일 이름 문자열.
*/
char	*get_tmp_filename(int i)
{
	char	*num_str;
	char	*name;

	num_str = ft_itoa(i); // 숫자를 문자열로 변환
	name = ft_strjoin(".heredoc_", num_str); // 접두사와 결합
	free(num_str); // 숫자 문자열 해제
	return (name); // 결과 반환
}

/*
** 함수 역할: Heredoc이 EOF로 종료되었을 때 경고 메시지 출력.
** @param start_line Heredoc 시작 라인 번호.
** @param limiter 기대했던 종료 구분자.
*/
void	print_heredoc_warning(int start_line, char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(start_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
}

/*
** 함수 역할: 입력된 라인을 파일에 씀. 필요 시 환경변수 확장 수행.
** @param fd 파일 디스크립터.
** @param line 입력된 문자열.
** @param quoted 구분자의 따옴표 여부 (확장 여부 결정).
** @param sh 쉘 상태 구조체.
** @return 항상 1 반환.
*/
int	write_line_to_fd(int fd, char *line, int quoted, t_shell *sh)
{
	char	*expanded;

	if (!quoted) // 따옴표가 없었던 경우에만 확장 수행
	{
		expanded = expand_str(line, sh); // 문자열 확장
		free(line); // 원본 해제
		line = expanded; // 확장된 문자열로 교체
	}
	write(fd, line, ft_strlen(line)); // 파일에 쓰기
	write(fd, "\n", 1); // 개행 쓰기
	free(line); // 메모리 해제
	return (1);
}
