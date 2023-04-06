/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:32:58 by fsandel           #+#    #+#             */
/*   Updated: 2023/04/06 15:52:36 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> //memset
# include <pthread.h> //pthread_create, pthread_detach, pthread_join
# include <stdio.h> //printf
# include <unistd.h> //write, fork, usleep
# include <stdlib.h> //malloc, free, exit
# include <sys/time.h> //gettimeofday
# include <sys/wait.h> //waitpid
# include <semaphore.h> //sem_open sem_close sem_post sem_wait sem_unlink
# include <signal.h> //kill

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# define RED "\033[0;31m"
# define DEFAULT "\033[0m"
# define YELLOW "\33[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define GREEN "\033[32m"

# define FORK_SEM "fork_sem"
# define PRINT_SEM "print_sem"
# define DEATH_SEM "death_sem"
# define KILL_SEM "kill_sem"
# define DONE_EATING_SEM "done_eating_sem"

typedef struct s_rules
{
	long			amount;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_eat;
	long			start;
	pid_t			*all_id;
	pthread_t		death_id;
	pthread_t		done_id;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*death;
	sem_t			*done_eating;
	sem_t			*kill;
}			t_rules;

typedef struct s_philo
{
	int				number;
	long			last_eating;
	long			times_to_eat;
	t_rules			*rules;
	pthread_t		waitress_id;
}		t_philo;

//input.c
int		check_arguments(int argc, char *argv[]);

//setup.c
t_rules	setup_rules(t_rules *rules, int argc, char *argv[]);
void	setup_philo(t_philo *philo, t_rules *rules, int i);
void	get_right_fork(t_philo **all_philos, t_rules *rules);

//state_change.c
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	sleeping(t_philo *philo);

//process.c
pid_t	*start_processes(t_rules *rules);
void	kill_processes(t_rules *rules);
void	*end_checker(void *arg);
void	*death_checker(void *arg);

//time.c
long	current_time_ms(void);
void	ft_sleep(long ms);

//utils.c
long	ft_atol(const char *str);
int		ft_isdigit(int arg);
size_t	ft_strlen(const char *str);
void	free_all(t_philo **all_philos, t_rules *rules);
void	philo_printf(t_philo *philo, char *string, char *color);

//waitress.c
void	*waitress_thread(void *arg);

#endif