/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:26:41 by imeftah-          #+#    #+#             */
/*   Updated: 2025/05/30 10:26:42 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_serror(t_init *data)
{
	if (data->n_ph <= 0 || data->t_die <= 0 || data->t_eat <= 0
		|| data->t_sleep <= 0 || data->nm_eat == -1)
		return (-1);
	return (0);
}

void	init_mutex(t_init *data)
{
	int	i;

	i = 0;
	while (i < data->n_ph)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->nmeal_lock, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
}

int	init_args(t_init *data, int ac, char **args)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (free(data), write(2, "error\n", 17), -1);
	else
	{
		data->start_time = get_time_in_ms();
		data->n_ph = ft_atoi(args[1]);
		data->t_die = ft_atoi(args[2]);
		data->t_eat = ft_atoi(args[3]);
		data->t_sleep = ft_atoi(args[4]);
		data->nm_eat = -2;
		data->dead = 0;
		if (ac == 6)
			data->nm_eat = ft_atoi(args[5]);
		if (check_serror(data) == -1)
			return (free(data), printf("error\n"), -1);
		data->forks = malloc(data->n_ph * sizeof(pthread_mutex_t));
		if (data->forks == NULL)
			return (free(data), -1);
		init_mutex(data);
	}
	return (0);
}

void	init_philos(t_init *data, t_phls *philo)
{
	int	i;

	i = 0;
	while (data->n_ph > i)
	{
		philo[i].id = i + 1;
		philo[i].init = data;
		philo[i].n_meal = 0;
		philo[i].last_meal = data->start_time;
		philo[i].left = &data->forks[i];
		if (i == data->n_ph - 1)
			philo[i].right = &data->forks[0];
		else
			philo[i].right = &data->forks[i + 1];
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor, philo);
}
