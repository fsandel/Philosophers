/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:45:20 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/16 19:18:15 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_dead(t_philo *philo)
{
	if (philo->last_eating + philo->rules->time_to_die < current_time_ms()
		&& philo->currently_eating == 0 && philo->times_to_eat > 0)
		return (1);
	else
		return (0);
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
