/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:27:39 by imeftah-          #+#    #+#             */
/*   Updated: 2025/05/30 16:24:37 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex_free(t_init *data, t_phls *philo)
{
	int	i;

	i = 0;
	while (i < data->n_ph)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->nmeal_lock);
	pthread_mutex_destroy(&data->print_lock);
	free(data->forks);
	free(data);
	free(philo);
}

int	main(int ac, char **av)
{
	t_init	*data;
	t_phls	*philo;
	int		i;

	i = 0;
	data = malloc(sizeof(t_init));
	if (!data)
		return (1);
	if (init_args(data, ac, av) == -1)
		return (1);
	philo = malloc(sizeof(t_phls) * data->n_ph);
	if (!philo)
	{
		free(data);
		return (1);
	}
	init_philos(data, philo);
	pthread_join(data->monitor, NULL);
	while (i < data->n_ph)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	destroy_mutex_free(data, philo);
}
