/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:08:20 by alejandj          #+#    #+#             */
/*   Updated: 2025/10/03 14:27:51 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	smart_usleep(t_sim *sim, long time_ms)
{
	long	start;
	int		dead;

	start = get_time_ms(sim);
	while (get_time_ms(sim) - start <= time_ms)
	{
		pthread_mutex_lock(&sim->death_mutex);
		dead = sim->someone_dead;
		pthread_mutex_unlock(&sim->death_mutex);
		if (dead)
			break ;
		usleep(500);
	}
}

void	fill_forks(t_fork *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&forks[i].fork, NULL);
		forks[i].fork_id = i + 1;
		i++;
	}
}

void	fill_philos(t_philo *philos, t_fork *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		philos[i].id = i + 1;
		if (i == 0)
		{
			philos[i].left_fork = &forks[num_philos - 1];
			philos[i].right_fork = &forks[i];
		}
		else
		{
			philos[i].left_fork = &forks[i - 1];
			philos[i].right_fork = &forks[i];
		}
		philos[i].num_meals = 0;
		philos[i].last_meal = 0;
		i++;
	}
}

void	free_forks(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_of_philo)
	{
		pthread_mutex_destroy(&sim->forks[i].fork);
		i++;
	}
	free(sim->forks);
}

void	clean_up(t_sim *sim)
{
	free_forks(sim);
	free(sim->philos);
	free(sim->threads);
	pthread_mutex_destroy(&sim->print_mutex);
}
