/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:57:06 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/29 15:51:11 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

// Forks
typedef	struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}					t_fork;

// Philos
typedef struct s_philo
{
	int		id;
	t_fork	*left_fork;
	t_fork	*right_fork;
	int		num_meals;
	long long last_meal;
}			t_philo;

// Simulation Data
typedef struct s_sim
{
	struct timeval start_time;
	int	num_of_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_times_eat;
	t_philo		*philos;
	t_fork		*forks;
	pthread_t	*threads;
	pthread_t dead_thread;
	int	someone_dead;
	int	all_saciated;
	pthread_mutex_t print_mutex;
}					t_sim;

// Args
typedef struct s_args
{
	t_philo	*philo;
	t_sim	*sim;
}			t_args;

// Utils
long		ft_atol(const char *str);
int			ft_isdigit(int c);
long long	get_time_ms(t_sim *sim);
void		print_status(t_sim *sim, int id, const char *msg);
void		show_error_args(void);
void		smart_usleep(t_sim *sim, long time_ms);
void		free_forks(t_sim *sim);
void		clean_up(t_sim *sim);

// Threads
void	manage_threads(t_sim *sim);
void	*philo_routine(void *arg);

// Actions
void	eat_action(t_philo *philo, t_sim *sim);
void    sleep_action(t_philo *philo, t_sim *sim);
void    think_action(t_philo *philo, t_sim *sim);

#endif