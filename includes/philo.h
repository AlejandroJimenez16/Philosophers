/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:57:06 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/04 21:51:36 by alejandj         ###   ########.fr       */
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

// Simulation Data
typedef struct s_sim
{
	struct timeval start_time;
	int	num_of_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_times_eat;
}		t_sim;

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
}			t_philo;

typedef struct s_args
{
	t_philo	*philo;
	t_sim	*sim;
}			t_args;

// Utils
int			ft_atoi(const char *str);
long long	get_time_ms(t_sim *sim);
void		show_error_args(void);

// Actions
void	eat_action(t_philo *philo, t_sim *sim);
void    sleep_action(t_philo *philo, t_sim *sim);
void    think_action(t_philo *philo, t_sim *sim);

#endif