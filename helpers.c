/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeftah- <imeftah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:20:39 by imeftah-          #+#    #+#             */
/*   Updated: 2025/05/30 10:23:11 by imeftah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
		return (-1);
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		if (nbr > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)nbr);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			some;

	gettimeofday(&tv, NULL);
	some = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (some);
}

void	save_printf(t_phls *philo, char *msg)
{
	pthread_mutex_lock(&philo->init->print_lock);
	if (death_checker(philo) == -1)
	{
		pthread_mutex_unlock(&philo->init->print_lock);
		return ;
	}
	printf("%ld %d %s\n", get_time_in_ms() - philo->init->start_time, philo->id,
		msg);
	pthread_mutex_unlock(&philo->init->print_lock);
}

int	ft_usleep(t_phls *data, long time)
{
	int	num_sleep;

	num_sleep = time / 50;
	while (time >= 50)
	{
		if (death_checker(data) == -1)
			return (-1);
		usleep(50 * 1000);
		time -= 50;
	}
	if (death_checker(data) == -1)
		return (-1);
	if (time > 0)
		usleep(time * 1000);
	return (0);
}
