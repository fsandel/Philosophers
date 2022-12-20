/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:31:37 by fsandel           #+#    #+#             */
/*   Updated: 2022/12/20 18:33:53 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *thread(void *arg)
{
	char *ret;
	static int i = 0;
	i++;
	ft_printf("entered ith argument %s\n", arg);
	ret = ft_strdup("--me child--");
	if (!ret)
	{
		perror("ft_strdup failed");
		exit(2);
	}
	//sleep(2);
	pthread_exit((void *)i);
}

int	main(void)
{
	pthread_t	thid;
	pthread_t	thid2;
	void		*ret;

	if (pthread_create(&thid, NULL, thread, "thread1"))
	{
		perror("pthread_create() error");
		exit(1);
	}
	if (pthread_join(thid, &ret))
	{
		perror("pthread_create() error");
		exit(3);
	}
	if (pthread_create(&thid2, NULL, thread, "thread1"))
	{
		perror("pthread_create() error");
		exit(1);
	}
	if (pthread_join(thid2, &ret))
	{
		perror("pthread_create() error");
		exit(3);
	}
	ft_printf("thread exited with %d\n", (int)ret);
	return (0);
}