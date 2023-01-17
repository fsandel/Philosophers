/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:51:10 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/17 13:29:57 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_rules	*setup_rules(int argc, char *argv[])
{
	t_rules	*rules;

	rules = (t_rules *)malloc(sizeof(t_rules));
	rules->amount = ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		rules->number_of_eat = ft_atol(argv[5]);
	else
		rules->number_of_eat = INT_MAX;
	return (rules);
}

t_philo	**setup_philos(t_rules *rules)
{
	long			time_in_ms;
	t_philo			**all_philos;
	int				i;

	all_philos = malloc(sizeof(t_philo) * rules->amount);
	i = 0;
	time_in_ms = current_time_ms();
	while (i < rules->amount)
	{
		all_philos[i] = malloc(sizeof(t_philo));
		all_philos[i]->number = i;
		all_philos[i]->start = time_in_ms;
		all_philos[i]->last_eating = time_in_ms;
		all_philos[i]->rules = rules;
		all_philos[i]->times_to_eat = rules->number_of_eat;
		all_philos[i]->is_dead = 0;
		pthread_mutex_init(&all_philos[i]->eat_mutex, NULL);
		pthread_mutex_init(&all_philos[i]->print, NULL);
		pthread_mutex_init(&all_philos[i]->left, NULL);
		i++;
	}
	return (all_philos);
}

void	get_right_fork(t_philo **all_philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->amount - 1)
	{
		all_philos[i]->right = &all_philos[i + 1]->left;
		i++;
	}
	all_philos[i]->right = &all_philos[0]->left;
}
