/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:08:20 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/29 15:51:16 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	smart_usleep(t_sim *sim, long time_ms)
{
	long	start;

	start = get_time_ms(sim);
	while (get_time_ms(sim) - start <= time_ms)
	{
		if (sim->someone_dead)
			break;
		usleep(500);
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

void    clean_up(t_sim *sim)
{
    free_forks(sim);
	free(sim->philos);
	free(sim->threads);
	pthread_mutex_destroy(&sim->print_mutex);
}