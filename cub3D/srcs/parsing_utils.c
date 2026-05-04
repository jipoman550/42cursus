/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 10:42:45 by sisung            #+#    #+#             */
/*   Updated: 2026/05/04 17:41:22 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief ft_split으로 할당된 2차원 문자열 배열의 메모리를 안전하게 해제합니다.
 * @details 메모리 누수(Memory Leak)를 방지하기 위해 배열 내부의 각 문자열과
 *          배열 포인터 자체를 순차적으로 free 합니다.
 * @param tokens 해제할 2차원 문자열 배열 포인터
 */
void	free_split(char **tokens)
{
	int	i;

	if (!tokens)
	{
		// 널 포인터인 경우 아무 작업도 하지 않고 반환 (안전 장치)
		return ;
	}
	i = 0;
	while (tokens[i])
	{
		// 배열 내부의 각 문자열(토큰) 메모리 해제
		free(tokens[i]);
		i++;
	}
	// 문자열 포인터 배열 자체의 메모리 해제
	free(tokens);
}

/**
 * @brief 문자열이 순수한 숫자로만 이루어져 있는지, Leading Zero가 없는지 검사합니다.
 * @details 임베디드 시스템에서 잘못된 진법 해석(8진수 등)을 막기 위해
 *          '0' 단일 문자는 허용하되 '0220'과 같은 형태는 에러로 처리합니다.
 * @param str 검사할 문자열
 * @return 유효한 순수 숫자 형태라면 1, 아니면 0
 */
static int	is_strict_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
	{
		// 문자열이 비어있거나 널 포인터이면 오류 반환
		return (0);
	}
	if (str[0] == '0' && str[1] != '\0')
	{
		// 단일 '0'이 아닌데 '0'으로 시작하면 (예: "012") Leading zero 오류로 간주
		return (0);
	}
	while (str[i])
	{
		// 문자열의 모든 문자가 숫자(0~9)인지 확인
		if (!ft_isdigit(str[i]))
		{
			return (0);
		}
		i++;
	}
	// 모든 검사를 통과하면 유효한 숫자로 간주
	return (1);
}

/**
 * @brief 원본 문자열에 포함된 콤마(',')의 개수를 정확히 셉니다.
 * @details ft_split은 끝에 붙은 구분자를 무시하므로, "220,100,0," 같은
 *          비정상적인(Trailing comma) 입력을 사전에 차단하기 위해 사용합니다.
 * @param str 콤마 개수를 셀 원본 문자열
 * @return 발견된 콤마의 총 개수
 */
static int	count_commas(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		// 문자열을 순회하며 콤마(',')가 발견될 때마다 카운트 증가
		if (str[i] == ',')
		{
			count++;
		}
		i++;
	}
	// 최종 콤마 개수 반환
	return (count);
}

/**
 * @brief "R,G,B" 형태의 문자열을 엄격하게 파싱하여 단일 int 값으로 병합합니다.
 * @details 중복 설정, 잘못된 콤마 개수, 0~255 범위 이탈, 불필요한 공백 등을
 *          모두 걸러내어 안전한 비트 연산(0x00RRGGBB)을 수행합니다.
 * @param color_field 파싱된 RGB 값을 저장할 변수의 주소
 * @param rgb_str 파싱할 "R,G,B" 형식의 원본 문자열
 * @return 성공 시 0, 어떠한 형태의 설정 오류라도 발견 시 -1
 */
int	parse_color(int *color_field, const char *rgb_str)
{
	char	**tokens;
	int		rgb[3];
	int		i;

	// 이미 색상값이 설정되어 있거나(중복 파싱 방지), 콤마의 개수가 정확히 2개가 아니면 에러 반환
	if (*color_field != -1 || count_commas(rgb_str) != 2)
		return (-1);
	// 콤마를 기준으로 문자열을 분리 (예: "255,100,50" -> ["255", "100", "50"])
	tokens = ft_split(rgb_str, ',');
	if (!tokens)
		// 메모리 할당 실패 시 에러 반환
		return (-1);
	i = -1;
	// 분리된 3개의 토큰(R, G, B)에 대해 유효성 검사 및 정수 변환 수행
	while (++i < 3)
	{
		// 토큰이 존재하지 않거나, 유효한 엄격한 숫자 형태(문자 포함/앞에 0 포함 등)가 아니면 루프 중단
		if (!tokens[i] || !is_strict_digit(tokens[i]))
			break ;
		// 문자열을 정수로 변환하여 rgb 배열에 저장
		rgb[i] = ft_atoi(tokens[i]);
		// 색상 값이 0 ~ 255 범위를 벗어나면 루프 중단
		if (rgb[i] < 0 || rgb[i] > 255)
			break ;
	}
	// i가 3이 아니라는 것은 위 루프에서 에러로 인해 중간에 break 되었음을 의미함
	// tokens[i] != NULL 검사는 분리된 토큰이 4개 이상(예: "255,100,50,0")일 때를 대비한 추가 검사
	if (i != 3 || tokens[i] != NULL)
	{
		free_split(tokens);
		return (-1);
	}
	// R, G, B 값을 비트 시프트 연산으로 병합하여 하나의 int (0x00RRGGBB)로 생성
	*color_field = ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
	// 동적 할당된 토큰 배열 메모리 해제
	free_split(tokens);
	return (0);
}
