/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:26:30 by imeftah-          #+#    #+#             */
/*   Updated: 2025/05/30 14:47:51 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX INT_MAX
# define PH_MAX 200

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_init
{
	int				n_ph;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nm_eat;
	int				dead;
	int				who;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	nmeal_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	pthread_t		monitor;
}					t_init;

typedef struct s_phls
{
	int				id;
	int				n_meal;
	long			last_meal;
	t_init			*init;
	pthread_t		thread;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;

}					t_phls;

int					ft_atoi(char *str);
int					init_args(t_init *data, int ar, char **args);
int					ft_usleep(t_phls *data, long time);
int					death_checker(t_phls *philo);
int					number_of_meal(t_phls *philo);
long				get_time_in_ms(void);
long				get_time_in_ms(void);
void				*routine(void *data);
void				*monitor(void *pls);
void				save_printf(t_phls *philo, char *msg);
void				lock_forks(t_phls *philo);
void				unlock_forks(t_phls *philo);
void				init_philos(t_init *data, t_phls *philo);
void				is_sleeping(t_phls *data);
void				is_thinking(t_phls *data);
void				is_eating(t_phls *philo);

#endif
