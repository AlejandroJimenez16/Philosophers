/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:57:06 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/25 16:47:26 by alejandj         ###   ########.fr       */
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

// Simulation Data
typedef struct s_sim
{
	struct timeval start_time;
	int	num_of_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_times_eat;
	int	someone_dead;
	pthread_mutex_t print_mutex;
}					t_sim;

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

// Threads
void	manage_threads(t_philo *philos, t_sim *sim);
void	*philo_routine(void *arg);

// Actions
void	eat_action(t_philo *philo, t_sim *sim);
void    sleep_action(t_philo *philo, t_sim *sim);
void    think_action(t_philo *philo, t_sim *sim);

#endif