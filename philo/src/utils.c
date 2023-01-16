/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:27 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/16 18:30:49 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atol(const char *str)
{
	int		i;
	long	out;
	int		vz;

	i = 0;
	out = 0;
	vz = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			vz = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		out += str[i] - '0';
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			out *= 10;
		i++;
	}
	return (out * vz);
}

int	ft_isdigit(int arg)
{
	if (arg >= '0' && arg <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_all(t_philo **all_philos, t_rules *rules)
{
	int	i;
	int	amount;

	i = 0;
	amount = rules->amount;
	while (i < amount)
	{
		pthread_mutex_destroy(&all_philos[i]->print);
		pthread_mutex_destroy(&all_philos[i]->left);
		free(all_philos[i]);
		i++;
	}
	free(all_philos);
	free(rules);
}

void	philo_printf(t_philo *philo, char *string, char *color)
{
	pthread_mutex_lock(&philo->print);
	printf("%s%ld \t%d\t %s%s\n", color,
		current_time_ms() - philo->start, philo->number, string, DEFAULT);
	pthread_mutex_unlock(&philo->print);
}
