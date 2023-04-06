/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifestyle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:03:19 by fsandel           #+#    #+#             */
/*   Updated: 2023/04/06 15:49:07 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_left_fork(t_philo *philo)
{
	sem_wait(philo->rules->fork);
	philo_printf(philo, "has taken a fork", GREEN);
}

void	take_right_fork(t_philo *philo)
{
	sem_wait(philo->rules->fork);
	philo_printf(philo, "has taken a fork", GREEN);
}

void	eat(t_philo *philo)
{
	take_left_fork(philo);
	take_right_fork(philo);
	philo->last_eating = current_time_ms();
	philo_printf(philo, "is eating", YELLOW);
	philo->times_to_eat--;
	if (philo->times_to_eat == 0)
		sem_post(philo->rules->done_eating);
	ft_sleep(philo->rules->time_to_eat);
	sem_post(philo->rules->fork);
	sem_post(philo->rules->fork);
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
