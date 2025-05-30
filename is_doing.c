/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_doing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:56:29 by imeftah-          #+#    #+#             */
/*   Updated: 2025/05/30 14:56:36 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_sleeping(t_phls *data)
{
	save_printf(data, "is sleeping");
	if (ft_usleep(data, data->init->t_sleep) == -1)
		return ;
}

void	is_thinking(t_phls *data)
{
	save_printf(data, "is thinking");
}

void	is_eating(t_phls *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(&philo->init->meal_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->init->meal_lock);
	save_printf(philo, "is eating");
	if (ft_usleep(philo, philo->init->t_eat) == -1)
	{
		unlock_forks(philo);
		return ;
	}
	pthread_mutex_lock(&philo->init->nmeal_lock);
	philo->n_meal++;
	pthread_mutex_unlock(&philo->init->nmeal_lock);
	unlock_forks(philo);
}
