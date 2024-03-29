/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:10:27 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/18 15:27:36 by fsandel          ###   ########.fr       */
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
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		i++;
		len++;
	}
	return (len);
}

void	free_all(t_philo **all_philos, t_rules *rules)
{
	int	i;
	int	amount;

	i = 0;
	amount = rules->amount;
	while (i < amount)
	{
		pthread_mutex_destroy(&all_philos[i]->left);
		pthread_mutex_destroy(&all_philos[i]->eat_mutex);
		pthread_mutex_destroy(&all_philos[i]->check);
		free(all_philos[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->global_print);
	free(all_philos);
	free(rules);
}

void	philo_printf(t_philo *philo, char *string, char *color)
{
	pthread_mutex_lock(&philo->rules->global_print);
	printf("%s%ld \t%d\t %s%s\n", color,
		current_time_ms() - philo->rules->start,
		philo->number + 1, string, DEFAULT);
	pthread_mutex_unlock(&philo->rules->global_print);
}
