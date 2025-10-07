/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:08:20 by alejandj          #+#    #+#             */
/*   Updated: 2025/10/07 13:26:14 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	fill_forks(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_of_philo)
	{
		pthread_mutex_init(&sim->forks[i].fork, NULL);
		sim->forks[i].fork_id = i + 1;
		i++;
	}
}

void	fill_philos(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_of_philo)
	{
		sim->philos[i].id = i + 1;
		if (i == 0)
		{
			sim->philos[i].left_fork = &sim->forks[sim->num_of_philo - 1];
			sim->philos[i].right_fork = &sim->forks[i];
		}
		else
		{
			sim->philos[i].left_fork = &sim->forks[i - 1];
			sim->philos[i].right_fork = &sim->forks[i];
		}
		sim->philos[i].num_meals = 0;
		sim->philos[i].last_meal = 0;
		pthread_mutex_init(&sim->philos[i].meal_mutex, NULL);
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
	int	i;

	i = 0;
	while (i < sim->num_of_philo)
	{
		pthread_mutex_destroy(&sim->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->death_mutex);
	free_forks(sim);
	free(sim->philos);
	free(sim->threads);
}
