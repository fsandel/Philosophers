/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:31:37 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/21 19:59:23 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_rules		rules;
	void		*ret;

	if (check_arguments(argc, argv))
		return (-1);
	rules = setup_rules(&rules, argc, argv);
	rules.all_id = start_processes(&rules);
	pthread_create(&rules.death_id, NULL, death_checker, &rules);
	pthread_create(&rules.done_id, NULL, end_checker, &rules);
	waitpid(0, NULL, 0);
	pthread_join(rules.death_id, &ret);
	pthread_join(rules.done_id, &ret);
	free(rules.all_id);
	return (0);
}
