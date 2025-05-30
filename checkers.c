/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:27:50 by imeftah-          #+#    #+#             */
/*   Updated: 2025/05/30 10:27:51 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	number_of_meal(t_phls *philo)
{
	pthread_mutex_lock(&philo->init->nmeal_lock);
	if (philo->n_meal == philo->init->nm_eat)
	{
		pthread_mutex_unlock(&philo->init->nmeal_lock);
		return (-1);
	}
	pthread_mutex_unlock(&philo->init->nmeal_lock);
	return (0);
}

int	death_checker(t_phls *philo)
{
	pthread_mutex_lock(&philo->init->dead_lock);
	if (philo->init->dead == 1 || number_of_meal(philo) == -1)
	{
		pthread_mutex_unlock(&philo->init->dead_lock);
		return (-1);
	}
	pthread_mutex_unlock(&philo->init->dead_lock);
	return (0);
}
