/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:30:40 by alejandj          #+#    #+#             */
/*   Updated: 2025/10/06 00:57:59 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_sim_over(t_sim *sim)
{
	int	dead;
	int	saciated;

	pthread_mutex_lock(&sim->death_mutex);
	dead = sim->someone_dead;
	saciated = sim->all_saciated;
	pthread_mutex_unlock(&sim->death_mutex);
	return (dead || saciated);
}

void	*philo_routine(void *arg)
{
	t_args	*args;
	t_philo	*philo;
	t_sim	*sim;

	args = (t_args *)arg;
	philo = args->philo;
	sim = args->sim;
	while (!is_sim_over(sim))
	{
		eat_action(philo, sim);
		sleep_action(philo, sim);
		think_action(philo, sim);
	}
	return (NULL);
}

static int	check_num_meals(t_sim *sim)
{
	int	all_eat;
	int	i;

	if (sim->num_times_eat != -1)
	{
		all_eat = 1;
		i = 0;
		while (i < sim->num_of_philo)
		{
			if (sim->philos[i].num_meals < sim->num_times_eat)
			{
				all_eat = 0;
				break ;
			}
			i++;
		}
		if (all_eat)
		{
			pthread_mutex_lock(&sim->death_mutex);
			sim->all_saciated = 1;
			pthread_mutex_unlock(&sim->death_mutex);
			return (1);
		}
	}
	return (0);
}

static void	report_dead(t_sim *sim, int i)
{
	if (!sim->someone_dead)
	{
		sim->someone_dead = 1;
		pthread_mutex_lock(&sim->print_mutex);
		printf("\033[31m%lld [%d] %s\033[0m\n", get_time_ms(sim),
			sim->philos[i].id, "died");
		pthread_mutex_unlock(&sim->print_mutex);
	}
}

void	*threads_dead(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	while (1)
	{
		i = -1;
		while (++i < sim->num_of_philo)
		{
			pthread_mutex_lock(&sim->death_mutex);
			if (get_time_ms(sim) >= sim->philos[i].last_meal + sim->time_die)
			{
				report_dead(sim, i);
				return (pthread_mutex_unlock(&sim->death_mutex), NULL);
			}
			pthread_mutex_unlock(&sim->death_mutex);
		}
		if (check_num_meals(sim))
			return (NULL);
		usleep(1000);
	}
}
