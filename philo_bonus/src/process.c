/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:47:17 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/23 14:07:45 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	process(int i, t_rules *rules)
{
	t_philo	philo;
	void	*ret;

	setup_philo(&philo, rules, i);
	pthread_create(&philo.waitress_id, NULL, waitress_thread, &philo);
	while (1)
	{
		eat(&philo);
		sleeping(&philo);
		think(&philo);
	}
	pthread_join(philo.waitress_id, ret);
	sleep(1);
}

pid_t	*start_processes(t_rules *rules)
{
	int		i;
	pid_t	*all_pid;
	pid_t	pid;

	i = 0;
	all_pid = (pid_t *)malloc(sizeof(pid_t) * rules->amount);
	while (i < rules->amount)
	{
		pid = fork();
		if (pid == 0)
		{
			free(all_pid);
			process(i, rules);
			exit(-1);
		}
		else
			all_pid[i] = pid;
		i++;
	}
	return (all_pid);
}

void	kill_processes(t_rules *rules)
{
	int	i;

	i = 0;
	sem_wait(rules->kill);
	while (i < rules->amount)
		kill(rules->all_id[i++], SIGKILL);
}

void	*end_checker(void *arg)
{
	t_rules	*rules;
	int		i;

	i = 0;
	rules = (t_rules *)arg;
	while (i < rules->amount)
	{
		sem_wait(rules->done_eating);
		i++;
	}
	kill_processes(rules);
	pthread_detach(rules->death_id);
	pthread_exit(NULL);
}

void	*death_checker(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	sem_wait(rules->death);
	kill_processes(rules);
	pthread_detach(rules->done_id);
	pthread_exit(NULL);
}
