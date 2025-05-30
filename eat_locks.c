/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_locks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:27:19 by imeftah-          #+#    #+#             */
/*   Updated: 2025/05/30 10:28:01 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_phls *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right);
		save_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->left);
		save_printf(philo, "has taken a fork");
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(philo->left);
		save_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->right);
		save_printf(philo, "has taken a fork");
	}
}

void	unlock_forks(t_phls *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
	}
	else
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
}
