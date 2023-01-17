/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:32:58 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/17 15:13:07 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <signal.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# define RED "\033[0;31m"
# define DEFAULT "\033[0m"
# define YELLOW "\33[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"

typedef struct s_rules
{
	long			amount;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_eat;
	long			start;
	pthread_mutex_t	global_print;
}			t_rules;

typedef struct s_philo
{
	int				number;
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
	long			last_eating;
	long			times_to_eat;
	t_rules			*rules;
	pthread_mutex_t	eat_mutex;
	pthread_t		id;
}		t_philo;

typedef struct s_waitress
{
	pthread_t		id;
	t_rules			*rules;
	t_philo			**all_philos;
}					t_waitres;

//input.c
int		check_arguments(int argc, char *argv[]);

//setup.c
t_rules	*setup_rules(int argc, char *argv[]);
t_philo	**setup_philos(t_rules *rules);
void	get_right_fork(t_philo **all_philos, t_rules *rules);

//state_change.c
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	sleeping(t_philo *philo);

//thread.c
void	start_threads(t_philo **all_philos, t_rules *rules);
void	*thread(void *arg);
void	join_threads(t_philo **all_philos, t_rules *rules);
void	detach_threads(t_philo **all_philos, t_rules *rules);

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
int		is_dead(t_philo *philo);
void	*waitres_thread(void *arg);
void	waitres_func(t_philo **all_philos, t_rules *rules);

#endif