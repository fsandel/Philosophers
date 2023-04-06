/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:42:23 by fsandel           #+#    #+#             */
/*   Updated: 2023/04/06 15:42:04 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	start_threads(t_philo **all_philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->amount)
	{
		pthread_create(&all_philos[i]->id, NULL, thread, all_philos[i]);
		i++;
	}
}

void	*thread(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->number % 4)
		ft_sleep(3);
	while (1)
	{
		eat(philo);
		sleeping(philo);
		think(philo);
	}
}

void	join_threads(t_philo **all_philos, t_rules *rules)
{
	int		i;
	void	*ret;

	i = 0;
	while (i < rules->amount)
		pthread_join(all_philos[i++]->id, &ret);
}

void	detach_threads(t_philo **all_philos, t_rules *rules)
{
	int		i;

	i = 0;
	while (i < rules->amount)
		pthread_detach(all_philos[i++]->id);
}
