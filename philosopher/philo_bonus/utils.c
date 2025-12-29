/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisung <sisung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:06:02 by sisung            #+#    #+#             */
/*   Updated: 2025/11/25 15:28:23 by sisung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	parse_required_args(t_data *data, char **argv)
{
	long long	val;
	size_t		i;

	i = 1;
	while (i <= 4)
	{
		val = ft_parse_long(argv[i]);
		if (val == -1)
			return (-1);
		if (i == 1)
			data->num_of_philos = (size_t)val;
		else if (i == 2)
			data->time_to_die = val;
		else if (i == 3)
			data->time_to_eat = val;
		else if (i == 4)
			data->time_to_sleep = val;
		i++;
	}
	return (0);
}
