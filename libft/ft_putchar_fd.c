/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:12:26 by sisung            #+#    #+#             */
/*   Updated: 2025/04/14 16:06:51 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

// #include <fcntl.h> // open
// #include <unistd.h> // write, close
// #include <stdio.h> // printf

// int main()
// {
// 	// 테스트 1: 유효하지 않은 fd
// 	ft_putchar_fd('a', -1); // 아무것도 출력되지 않아야 함

// 	// 테스트 2: stdout (fd = 1)
// 	ft_putchar_fd('b', 1); // 콘솔에 b 출력
// 	write(1, "\n", 1);

// 	// 테스트 3: stderr (fd = 2)
// 	ft_putchar_fd('c', 2); // 에러 스트림에 출력
// 	write(2, "\n", 1);

// 	// 테스트 4: 파일에 출력
// 	int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd >= 0)
// 	{
// 		ft_putchar_fd('d', fd); // 파일에 'd' 기록
// 		close(fd);
// 	}

// 	return 0;
// }