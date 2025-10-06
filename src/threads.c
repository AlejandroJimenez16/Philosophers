/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:58:21 by alejandj          #+#    #+#             */
/*   Updated: 2025/10/07 00:37:48 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	create_threads(t_sim *sim, t_args *args)
{
	int	i;

	i = 0;
	while (i < sim->num_of_philo)
	{
		args[i].philo = &sim->philos[i];
		args[i].sim = sim;
		pthread_create(&sim->threads[i], NULL, philo_routine, &args[i]);
		i++;
	}
	usleep(5000);
	pthread_create(&sim->dead_thread, NULL, threads_dead, sim);
}

void	manage_threads(t_sim *sim)
{
	t_args		*args;
	int			i;

	i = 0;
	sim->threads = malloc(sim->num_of_philo * sizeof(pthread_t));
	if (!sim->threads)
		return (free(sim->philos), free_forks(sim));
	args = malloc(sim->num_of_philo * sizeof(t_args));
	if (!args)
		return (free(sim->philos), free_forks(sim), free(sim->threads));
	create_threads(sim, args);
	while (i < sim->num_of_philo)
	{
		pthread_join(sim->threads[i], NULL);
		i++;
	}
	pthread_join(sim->dead_thread, NULL);
	free(args);
}
