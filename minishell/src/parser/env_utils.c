/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:22:02 by sisung            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:38 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

/*
** 함수 역할: 환경변수 배열(char **) 메모리 해제.
** @param envp 해제할 환경변수 배열.
*/
void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i]) // 배열 순회
	{
		free(envp[i]); // 각 문자열 해제
		i++;
	}
	free(envp); // 배열 자체 해제
}

/*
** 함수 역할: 두 문자열을 안전하게 결합하고 첫 번째 문자열 해제.
** @param s1 기존 문자열 (해제됨).
** @param s2 추가할 문자열.
** @return 결합된 새 문자열.
*/
char	*safe_join(char *s1, char *s2)
{
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2); // 문자열 결합
	free(s1); // 첫 번째 문자열 해제
	return (new_str);
}

/*
** 함수 역할: 환경변수 문자열에서 키(Key)의 길이를 계산 (등호 전까지).
** @param env_str "KEY=VALUE" 형태의 문자열.
** @return 키의 길이.
*/
static int	get_key_len(char *env_str)
{
	int	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=') // 등호나 끝을 만날 때까지
		i++;
	return (i);
}

/*
** 함수 역할: 키(Key)에 해당하는 환경변수 값(Value)을 찾아 반환.
** @param key 찾을 환경변수 키.
** @param sh 쉘 상태 구조체.
** @return 값의 복사본 (없으면 빈 문자열).
*/
char	*get_env_value(char *key, t_shell *sh)
{
	int		i;
	int		key_len;

	if (ft_strncmp(key, "?", 2) == 0) // $? 인 경우
		return (ft_itoa(sh->last_status)); // 마지막 종료 상태 반환
	i = 0;
	while (sh->envp && sh->envp[i]) // 환경변수 목록 순회
	{
		key_len = get_key_len(sh->envp[i]); // 현재 환경변수의 키 길이 계산
		if ((int)ft_strlen(key) == key_len && \
			ft_strncmp(key, sh->envp[i], key_len) == 0) // 키가 일치하면
		{
			return (ft_strdup(sh->envp[i] + key_len + 1)); // 값 부분 복제하여 반환
		}
		i++;
	}
	return (ft_strdup("")); // 없으면 빈 문자열 반환
}
