/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:24:57 by suylee            #+#    #+#             */
/*   Updated: 2021/07/26 20:33:44 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->base->fork[philo->l_fork]));
	print_all(philo->base, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->base->fork[philo->r_fork]));
	print_all(philo->base, philo->id, "has taken a fork");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->base->meal_check));
	print_all(philo->base, philo->id, "is eating");
	philo->t_leat = timestamp();
	pthread_mutex_unlock(&(philo->base->meal_check));
	my_usleep(philo->base->t_eat, philo->base);
	(philo->x_ate)++;
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->base->fork[philo->l_fork]));
	pthread_mutex_unlock(&(philo->base->fork[philo->r_fork]));
}

void	*philosopher(void *void_philosopher)
{
	t_philo	*philo;
	t_all	*base;

	philo = (t_philo *)void_philosopher;
	base = philo->base;
	if (philo->id % 2)
		usleep(10000);
	while (!(base->dieded))
	{
		lock_fork(philo);
		eat(philo);
		unlock_fork(philo);
		if (base->all_ate)
			break ;
		print_all(base, philo->id, "is sleeping");
		my_usleep(base->t_sleep, base);
		print_all(base, philo->id, "is thinking");
	}
	return (NULL);
}

void	is_death(t_all *dp, t_philo *philo)
{
	int	i;

	while (!(dp->all_ate))
	{
		i = -1;
		while (++i < dp->nb_philo && !(dp->dieded))
		{
			pthread_mutex_lock(&(dp->meal_check));
			if (time_diff(philo[i].t_leat, timestamp()) > dp->t_die)
			{
				print_all(dp, i, "died");
				dp->dieded = 1;
			}
			pthread_mutex_unlock(&(dp->meal_check));
			usleep(100);
		}
		if (dp->dieded)
			break ;
		i = 0;
		while (dp->nb_eat != -1 && i < dp->nb_philo
			&& philo[i].x_ate >= dp->nb_eat)
			i++;
		if (i == dp->nb_philo)
			dp->all_ate = 1;
	}
}
