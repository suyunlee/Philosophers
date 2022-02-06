/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 00:16:21 by suylee            #+#    #+#             */
/*   Updated: 2021/07/27 00:20:38 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

int	ft_atoi(char *str)
{
	size_t	i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			return (-1);
		i++;
	}
	return (result);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	my_usleep(long long time, t_all *base)
{
	long long	i;

	i = timestamp();
	while (!(base->dieded))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	print_all(t_all *base, int id, char *str)
{
	sem_wait(base->writing);
	if (!(base->dieded))
	{
		printf("%llims ", timestamp() - base->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	sem_post(base->writing);
	return ;
}
