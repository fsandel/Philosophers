/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:03:19 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/18 15:46:57 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left);
	philo_printf(philo, "has taken a fork", GREEN);
}

void	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	philo_printf(philo, "has taken a fork", GREEN);
}

void	eat(t_philo *philo)
{
	if (philo->number % 2)
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
	else
	{
		take_right_fork(philo);
		take_left_fork(philo);
	}
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eating = current_time_ms();
	philo_printf(philo, "is eating", YELLOW);
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_lock(&philo->check);
	philo->times_to_eat--;
	pthread_mutex_unlock(&philo->check);
	ft_sleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(philo->right);
}

void	think(t_philo *philo)
{
	philo_printf(philo, "is thinking", PURPLE);
}

void	sleeping(t_philo *philo)
{
	philo_printf(philo, "is sleeping", CYAN);
	ft_sleep(philo->rules->time_to_sleep);
}
