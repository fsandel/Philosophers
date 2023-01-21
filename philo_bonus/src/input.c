/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:05:16 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/16 19:25:46 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	bad_input_message(void);
int	check_digit(int argc, char *argv[]);
int	check_max_size(int argc, char *argv[]);
int	check_min_size(int argc, char *argv[]);

int	check_arguments(int argc, char *argv[])
{
	if (!(argc == 6 || argc == 5))
		return (bad_input_message());
	if (check_digit(argc, argv))
		return (bad_input_message());
	if (check_max_size(argc, argv))
		return (bad_input_message());
	if (check_min_size(argc, argv))
		return (bad_input_message());
	return (0);
}

int	bad_input_message(void)
{
	printf("Please enter following arguments\n");
	printf("number_of_philosophers\n");
	printf("time_to_die\t(in ms)\n");
	printf("time_to_eat\t(in ms)\n");
	printf("time_to_sleep \t(in ms)\n");
	printf("number_of_times_each_philosopher_must_eat (optional)\n");
	printf("only positive numbers in integer range are allowed\n");
	return (-1);
}

int	check_digit(int argc, char *argv[])
{
	int	i;
	int	j;

	j = 1;
	while (j < argc)
	{
		i = 0;
		if (argv[j][0] == 0)
			return (-1);
		while (argv[j][i])
		{
			if (ft_isdigit(argv[j][i++]) == 0)
				return (-1);
		}
		j++;
	}
	return (0);
}

int	check_max_size(int argc, char *argv[])
{
	int	j;

	j = 1;
	while (j < argc)
	{
		if (ft_strlen(argv[j]) > 10)
			return (-1);
		if (ft_atol(argv[j]) > INT_MAX)
			return (-1);
		j++;
	}
	return (0);
}

int	check_min_size(int argc, char *argv[])
{
	int			j;
	const int	min_values[] = {0, 1, 1, 1, 1, 1};

	j = 1;
	while (j < argc)
	{
		if (ft_atol(argv[j]) < min_values[j])
			return (-1);
		j++;
	}
	return (0);
}
