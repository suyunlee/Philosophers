/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 00:08:35 by suylee            #+#    #+#             */
/*   Updated: 2021/07/27 00:16:01 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

int	process_init(t_all *base)
{
	int		i;
	t_philo	*phi;

	i = 0;
	phi = base->philo;
	base->first_timestamp = timestamp();
	while (i < base->nb_philo)
	{
		phi[i].p_id = fork();
		if (phi[i].p_id < 0)
			return (-1);
		if (phi[i].p_id == 0)
			philosopher(&(phi[i]));
		usleep(100);
		i++;
	}
	exit_process(base);
	return (0);
}

int	init_philo(t_all *base)
{
	int	i;

	i = -1;
	while (++i < base->nb_philo)
	{
		base->philo[i].id = i;
		base->philo[i].x_ate = 0;
		base->philo[i].t_leat = 0;
		base->philo[i].base = base;
	}
	sem_unlink("/philo_fork");
	sem_unlink("/philo_write");
	sem_unlink("/philo_mealcheck");
	base->fork = sem_open("/philo_fork", O_CREAT, S_IRWXU, base->nb_philo);
	base->writing = sem_open("/philo_write", O_CREAT, S_IRWXU, 1);
	base->meal_check = sem_open("/philo_mealcheck", O_CREAT, S_IRWXU, 1);
	return (0);
}

int	init_all(t_all *base, char **argv)
{
	base->nb_philo = ft_atoi(argv[1]);
	base->t_die = ft_atoi(argv[2]);
	base->t_eat = ft_atoi(argv[3]);
	base->t_sleep = ft_atoi(argv[4]);
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
	if (process_init(&dining_philosophers))
		return (write_error("error creating the threads\n"));
	return (0);
}
