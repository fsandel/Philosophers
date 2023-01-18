/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:31:37 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/18 13:21:45 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_rules		*rules;
	t_philo		**all_philos;

	if (check_arguments(argc, argv))
		return (-1);
	rules = setup_rules(argc, argv);
	all_philos = setup_philos(rules);
	get_right_fork(all_philos, rules);
	start_threads(all_philos, rules);
	waitres_func(all_philos, rules);
	join_threads(all_philos, rules);
	free_all(all_philos, rules);
	return (0);
}
