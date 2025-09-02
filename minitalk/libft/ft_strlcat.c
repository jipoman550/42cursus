/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:56:05 by sisung            #+#    #+#             */
/*   Updated: 2025/04/23 11:31:10 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (dsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len >= dsize)
		return (dsize + src_len);
	i = 0;
	while (src[i] && dst_len + i < (dsize - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
