/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:38:40 by suylee            #+#    #+#             */
/*   Updated: 2021/07/26 20:45:57 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_init(t_all *base)
{
	int		i;
	t_philo	*phi;

	i = 0;
	phi = base->philo;
	base->first_timestamp = timestamp();
	while (i < base->nb_philo)
	{
		if (pthread_create(&(phi[i].tid), NULL, philosopher, (void *)&(phi[i])))
			return (-1);
		phi[i].t_leat = timestamp();
		i++;
	}
	is_death(base, base->philo);
	i = -1;
	while (++i < base->nb_philo)
		pthread_join(phi[i].tid, NULL);
	i = -1;
	while (++i < base->nb_philo)
		pthread_mutex_destroy(&(base->fork[i]));
	pthread_mutex_destroy(&(base->writing));
	pthread_mutex_destroy(&(base->meal_check));
	return (0);
}

int	init_philo(t_all *base)
{
	int	i;

	i = -1;
	base->philo = malloc(sizeof(t_philo) * base->nb_philo);
	base->fork = malloc(sizeof(pthread_mutex_t) * base->nb_philo);
	if (!base->philo || !base->fork)
		return (-1);
	while (++i < base->nb_philo)
	{
		base->philo[i].id = i;
		base->philo[i].x_ate = 0;
		base->philo[i].l_fork = i;
		base->philo[i].r_fork = (i + 1) % base->nb_philo;
		base->philo[i].t_leat = 0;
		base->philo[i].base = base;
		if (pthread_mutex_init(&base->fork[i], NULL))
			return (-1);
	}
	if (pthread_mutex_init(&(base->writing), NULL))
		return (-1);
	if (pthread_mutex_init(&(base->meal_check), NULL))
		return (-1);
	return (0);
}

int	init_all(t_all *base, char **argv)
{
	base->nb_philo = ft_atoi(argv[1]);
	base->t_die = ft_atoi(argv[2]);
	base->t_eat = ft_atoi(argv[3]);
	base->t_sleep = ft_atoi(argv[4]);
	base->all_ate = 0;
	base->dieded = 0;
	if (base->nb_philo < 1 || base->t_die < 0 || base->t_eat < 0
		|| base->t_sleep < 0)
		return (-1);
	if (argv[5])
	{
		base->nb_eat = ft_atoi(argv[5]);
		if (base->nb_eat < 0)
			return (-1);
	}
	else
		base->nb_eat = -1;
	if (init_philo(base))
		return (-1);
	return (0);
}

int	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	return (-1);
}

int	main(int argc, char **argv)
{
	t_all	dining_philosophers;
	int		i;

	if (argc != 5 && argc != 6)
		return (write_error("Wrong arguments\n"));
	i = init_all(&dining_philosophers, argv);
	if (i != 0)
		return (write_error("error init\n"));
	if (thread_init(&dining_philosophers))
	{
		return (write_error("error creating the threads\n"));
	}
	free(dining_philosophers.philo);
	return (0);
}
