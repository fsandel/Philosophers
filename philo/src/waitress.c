/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:45:20 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/17 13:55:38 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	kill_philos(t_waitres *waitres)
{
	int	i;

	i = 0;
	while (i < waitres->rules->amount)
	{
		waitres->all_philos[i++]->is_dead = 0;
	}
}

void	kill_print(t_philo *philo)
{
	ft_sleep(2);
	pthread_mutex_lock(&philo->print);
	printf("%s%ld \t%d\t %s%s\n", RED,
	current_time_ms() - philo->start, philo->number + 1, "died", DEFAULT);
	pthread_mutex_unlock(&philo->print);
}
int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	if (philo->last_eating + philo->rules->time_to_die < current_time_ms()
		&& philo->times_to_eat > 0)
		{
			pthread_mutex_unlock(&philo->eat_mutex);
			return (1);
		}
	else
	{
			pthread_mutex_unlock(&philo->eat_mutex);
			return (0);
	}
}

void	*waitres_thread(void *arg)
{
	int			is_finished;
	int			philo_num;
	t_waitres	*waitres;

	waitres = (t_waitres *)arg;
	while (1)
	{
		philo_num = 0;
		is_finished = 1;
		while (philo_num < waitres->rules->amount)
		{
			if (is_dead(waitres->all_philos[philo_num]))
			{
				philo_printf(waitres->all_philos[philo_num], "is dead", RED);
				kill_philos(waitres);
				kill_print(waitres->all_philos[philo_num]);
				pthread_exit("1");
			}
			if (waitres->all_philos[philo_num]->times_to_eat != 0)
				is_finished = 0;
			philo_num++;
		}
		if (is_finished)
			pthread_exit(NULL);
	}
	return (NULL);
}

void	waitres_func(t_philo **all_philos, t_rules *rules)
{
	t_waitres	*waitres;
	void		*ret;

	ret = NULL;
	waitres = malloc(sizeof(t_waitres));
	waitres->rules = rules;
	waitres->all_philos = all_philos;
	pthread_mutex_init((&waitres->print), NULL);
	pthread_create(&waitres->id, NULL, waitres_thread, waitres);
	pthread_join(waitres->id, &ret);
	if (ret)
		detach_threads(all_philos, rules);
	free(waitres);
}
