/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jaeholee <makest@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:26:06 by Jaeholee          #+#    #+#             */
/*   Updated: 2025/07/24 18:26:07 by Jaeholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#ifndef BSIZE
# define BSIZE 1024
#endif

int	ft_strlen(char *string)
{
	int i = 0;
	if (!string)
		return (0);
	while (string[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	char *buf;
	char *string = NULL;
	int	readbyte;

	if (argc != 2)
		return (printf("1\n"), 1);
	if (!argv[1] || !*argv[1])
		return (printf("2\n"), 1);
	buf = calloc(sizeof(char), BSIZE + 1);
	if (!buf)
		return (perror("Error :"), 1);
	//*/
	
	int fd = open("/home/jaeholee/text.txt", O_RDONLY);
	//int fd = 0;
	//*/
	size_t string_len = 0;
	while ((readbyte = read(fd, buf, BSIZE)) > 0)
	{
		char *tmp = realloc(string, string_len + readbyte + 1);
		if (!tmp)
			return (free(string), free(buf), perror("Error :"), 1);
		string = tmp;
		memmove(&string[string_len], buf, readbyte);
		string_len += (size_t)readbyte;
		string[string_len] = '\0'; 
	}
	free(buf);
	if (readbyte < 0)
		return (perror("Error :"), 1);
	//printf("string :[%s]\n", string);
	char *find = NULL;
	ssize_t word_len = strlen(argv[1]);
	char *pre_find = string;
	while (1)
	{
		find = memmem(pre_find, strlen(pre_find), argv[1], word_len);
		if (!find)
			break ;
		ssize_t find_t = word_len; 
		while (find_t)
		{
			*find = '*';
			find++;
			find_t--;
		}
		pre_find = find;
	}
	//printf("string :[%s]\n", string);
	write(1, string, strlen(string));
	free(string);
}



















