/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:45:20 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/18 15:58:32 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	if (philo->last_eating + philo->rules->time_to_die < current_time_ms())
		return (1);
	else
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		return (0);
	}
}

void	*waitress_thread(void *arg)
{
	int			is_finished;
	int			philo_num;
	t_waitress	*waitress;

	waitress = (t_waitress *)arg;
	while (1)
	{
		philo_num = 0;
		is_finished = 1;
		while (philo_num < waitress->rules->amount)
		{
			if (is_dead(waitress->all_philos[philo_num]))
				pthread_exit(waitress->all_philos[philo_num]);
			pthread_mutex_lock(&waitress->all_philos[philo_num]->check);
			if (waitress->all_philos[philo_num]->times_to_eat > 0)
				is_finished = 0;
			pthread_mutex_unlock(&waitress->all_philos[philo_num]->check);
			philo_num++;
		}
		if (is_finished)
			pthread_exit(NULL);
	}
	return (NULL);
}

void	waitress_func(t_philo **all_philos, t_rules *rules)
{
	t_waitress	*waitress;
	void		*ret;
	t_philo		*philo;

	waitress = malloc(sizeof(t_waitress));
	waitress->rules = rules;
	waitress->all_philos = all_philos;
	pthread_create(&waitress->id, NULL, waitress_thread, waitress);
	pthread_join(waitress->id, &ret);
	pthread_mutex_lock(&waitress->rules->global_print);
	if (ret)
	{
		detach_threads(all_philos, rules);
		philo = (t_philo *)ret;
		printf("%s%ld \t%d\t %s%s\n", RED,
			current_time_ms() - philo->rules->start,
			philo->number + 1, "died", DEFAULT);
	}
	else
		detach_threads(all_philos, rules);
	free(waitress);
}
