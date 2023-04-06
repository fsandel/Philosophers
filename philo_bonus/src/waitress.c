/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:45:20 by fsandel           #+#    #+#             */
/*   Updated: 2023/04/06 15:48:49 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_dead(t_philo *philo)
{
	if (philo->last_eating + philo->rules->time_to_die < current_time_ms())
		return (1);
	else
	{
		return (0);
	}
}

void	*waitress_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_dead(philo))
		{
			sem_wait(philo->rules->print);
			printf("%s%ld \t%d\t %s%s\n", RED,
				current_time_ms() - philo->rules->start,
				philo->number + 1, "died", DEFAULT);
			sem_post(philo->rules->death);
		}
		usleep(50);
	}
	return (NULL);
}
