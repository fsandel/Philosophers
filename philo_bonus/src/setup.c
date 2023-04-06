/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:51:10 by fsandel           #+#    #+#             */
/*   Updated: 2023/04/06 15:48:56 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_rules	setup_rules(t_rules *rules, int argc, char *argv[])
{
	rules->amount = ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	rules->start = current_time_ms();
	sem_unlink(FORK_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(DEATH_SEM);
	sem_unlink(DONE_EATING_SEM);
	sem_unlink(KILL_SEM);
	rules->kill = sem_open(KILL_SEM, O_CREAT, S_IRUSR | S_IWUSR, 1);
	rules->done_eating = sem_open(DONE_EATING_SEM,
			O_CREAT, S_IRUSR | S_IWUSR, 0);
	rules->death = sem_open(DEATH_SEM, O_CREAT, S_IRUSR | S_IWUSR, 0);
	rules->fork = sem_open(FORK_SEM, O_CREAT, S_IRUSR | S_IWUSR, rules->amount);
	rules->print = sem_open(PRINT_SEM, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (argc == 6)
		rules->number_of_eat = ft_atol(argv[5]);
	else
		rules->number_of_eat = -1;
	return (*rules);
}

void	setup_philo(t_philo *philo, t_rules *rules, int i)
{
	philo->number = i;
	philo->last_eating = rules->start;
	philo->rules = rules;
	philo->times_to_eat = rules->number_of_eat;
}
