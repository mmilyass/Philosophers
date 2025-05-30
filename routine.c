/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:20:52 by imeftah-          #+#    #+#             */
/*   Updated: 2025/05/30 14:56:19 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*is_dead(t_phls *philo)
{
	long	last;
	long	current_time;

	pthread_mutex_lock(&philo->init->meal_lock);
	last = philo->last_meal;
	current_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->init->meal_lock);
	if ((current_time - last >= philo->init->t_die))
	{
		save_printf(philo, "died");
		pthread_mutex_lock(&philo->init->dead_lock);
		philo[0].init->dead = 1;
		pthread_mutex_unlock(&philo->init->dead_lock);
		return (NULL);
	}
	return ("yes");
}

void	*routine(void *data)
{
	t_phls	*philo;

	philo = (t_phls *)data;
	if (philo->init->n_ph == 1)
	{
		is_thinking(philo);
		save_printf(philo, "has taken a fork");
		usleep(philo->init->t_die * 1000);
		save_printf(philo, "died");
		pthread_mutex_lock(&philo->init->dead_lock);
		philo->init->dead = 1;
		pthread_mutex_unlock(&philo->init->dead_lock);
		return (NULL);
	}
	while (1)
	{
		is_thinking(philo);
		if (death_checker(philo) == -1)
			break ;
		is_eating(philo);
		if (death_checker(philo) == -1)
			break ;
		is_sleeping(philo);
	}
	return (NULL);
}

void	*monitor(void *pls)
{
	t_phls	*philo;
	int		i;

	philo = (t_phls *)pls;
	while (1)
	{
		i = 0;
		while (i < philo[0].init->n_ph)
		{
			if (is_dead(&philo[i]) == NULL)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
