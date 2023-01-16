/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:03:19 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/16 19:23:11 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_left_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->left))
		philo_printf(philo, "failed locking left fork\n", RED);
	else
		philo_printf(philo, "has taken a fork", YELLOW);
}

void	take_right_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->right))
		philo_printf(philo, "failed locking right fork\n", RED);
	else
		philo_printf(philo, "has taken a fork", YELLOW);
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
	philo_printf(philo, "is eating", BLUE);
	philo->currently_eating = 1;
	philo->last_eating = current_time_ms();
	ft_sleep(philo->rules->time_to_eat);
	if (pthread_mutex_unlock(&philo->left))
		philo_printf(philo, "failed unlocking left fork\n", RED);
	if (pthread_mutex_unlock(philo->right))
		philo_printf(philo, "failed unlocking right fork\n", RED);
	philo->times_to_eat--;
	philo->currently_eating = 0;
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
