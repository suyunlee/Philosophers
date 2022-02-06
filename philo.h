/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:47:07 by suylee            #+#    #+#             */
/*   Updated: 2021/07/26 20:53:12 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_philo
{
	int					id;
	int					x_ate;
	int					l_fork;
	int					r_fork;
	long long			t_leat;
	struct s_all		*base;
	pthread_t			tid;
}				t_philo;

typedef struct s_all
{
	int					nb_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					nb_eat;
	int					dieded;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		writing;
	pthread_mutex_t		*fork;
	t_philo				*philo;
}				t_all;

int			thread_init(t_all *base);
int			init_philo(t_all *base);
int			init_all(t_all *base, char **argv);

void		lock_fork(t_philo *philo);
void		eat(t_philo *philo);
void		unlock_fork(t_philo *philo);
void		*philosopher(void *void_philosopher);
void		is_death(t_all *dp, t_philo *philo);

int			ft_atoi(char *str);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void		my_usleep(long long time, t_all *base);
void		print_all(t_all *base, int id, char *str);

#endif
