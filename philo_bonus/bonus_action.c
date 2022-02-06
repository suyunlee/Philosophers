/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 00:04:12 by suylee            #+#    #+#             */
/*   Updated: 2021/07/27 10:08:45 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

void	lock_fork(t_philo *philo)
{
	sem_wait(philo->base->fork);
	print_all(philo->base, philo->id, "has taken a fork");
	sem_wait(philo->base->fork);
	print_all(philo->base, philo->id, "has taken a fork");
}

void	eat_n_unlock_fork(t_philo *philo)
{
	sem_wait(philo->base->meal_check);
	print_all(philo->base, philo->id, "is eating");
	philo->t_leat = timestamp();
	sem_post(philo->base->meal_check);
	my_usleep(philo->base->t_eat, philo->base);
	(philo->x_ate)++;
	sem_post(philo->base->fork);
	sem_post(philo->base->fork);
}

void	*is_death(void *void_philo)
{
	t_philo	*philo;
	t_all	*dp;

	philo = (t_philo *)void_philo;
	dp = philo->base;
	while (1)
	{
		sem_wait(dp->meal_check);
		if (time_diff(philo->t_leat, timestamp()) > dp->t_die)
		{
			print_all(dp, philo->id, "died");
			dp->dieded = 1;
			sem_wait(dp->writing);
			exit(1);
		}
		sem_post(dp->meal_check);
		if (dp->dieded)
			break ;
		usleep(1000);
		if (philo->x_ate >= dp->nb_eat && dp->nb_eat != -1)
			break ;
	}
	return (NULL);
}

void	philosopher(void *void_philo)
{
	t_philo	*philo;
	t_all	*base;

	philo = (t_philo *)void_philo;
	base = philo->base;
	philo->t_leat = timestamp();
	pthread_create(&(philo->is_death), NULL, is_death, void_philo);
	if (philo->id % 2)
		usleep(10000);
	while (!(base->dieded))
	{
		lock_fork(philo);
		eat_n_unlock_fork(philo);
		if (philo->x_ate >= base->nb_eat && base->nb_eat != -1)
			break ;
		print_all(base, philo->id, "is sleeping");
		my_usleep(base->t_sleep, base);
		print_all(base, philo->id, "is thinking");
	}
	pthread_join(philo->is_death, NULL);
	if (base->dieded)
		exit(1);
	exit(0);
}

void	exit_process(t_all *base)
{
	int	i;
	int	status;

	i = 0;
	while (i < base->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < base->nb_philo)
				kill(base->philo[i].p_id, 9);
			break ;
		}
		i++;
	}
	sem_close(base->fork);
	sem_close(base->writing);
	sem_close(base->meal_check);
	sem_unlink("/philo_fork");
	sem_unlink("/philo_write");
	sem_unlink("/philo_mealcheck");
}
