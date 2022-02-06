/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 00:20:53 by suylee            #+#    #+#             */
/*   Updated: 2021/07/27 00:26:17 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PHILO_H
# define BONUS_PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>

typedef struct s_philo
{
	int					id;
	int					x_ate;
	long long			t_leat;
	struct s_all		*base;
	pthread_t			is_death;
	pid_t				p_id;
}						t_philo;

typedef struct s_all
{
	int					nb_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					nb_eat;
	int					dieded;
	long long			first_timestamp;
	sem_t				*meal_check;
	sem_t				*writing;
	sem_t				*fork;
	t_philo				philo[201];
}						t_all;

int			init_all(t_all *base, char **argv);
int			init_philo(t_all *base);
int			process_init(t_all *base);

void		lock_fork(t_philo *philo);
void		eat_n_unlock_fork(t_philo *philo);
void		*is_death(void *void_philo);
void		philosopher(void *void_philo);
void		exit_process(t_all *base);

int			ft_atoi(char *str);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void		my_usleep(long long time, t_all *base);
void		print_all(t_all *base, int id, char *str);

#endif
