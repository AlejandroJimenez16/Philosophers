/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:58:21 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/25 16:44:14 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_args *args = (t_args *)arg;
	t_philo *philo = args->philo;
	t_sim *sim = args->sim;

	while (1)
	{
		eat_action(philo, sim);
		sleep_action(philo, sim);
		think_action(philo, sim);
	}
	return (NULL);
}

void	*threads_dead(void *arg)
{
	t_args	*args = (t_args *)arg;
	t_philo *philo = args->philo;
	t_sim	*sim = args->sim;

	
}

void	create_threads(t_sim *sim, t_philo *philos, pthread_t *threads)
{
	pthread_t	dead_thread;
	t_args		*args;
	t_args		args_dead;
	int	i;

	args = malloc(sim->num_of_philo * sizeof(t_args));
	if (!args)
		return ;
	i = 0;
	while (i < sim->num_of_philo)
	{
		args[i].philo = &philos[i];
		args[i].sim = sim;
		pthread_create(&threads[i], NULL, philo_routine, &args[i]);
		i++;
	}
	args_dead.philo = philos;
	args_dead.sim = sim;
	pthread_create(&dead_thread, NULL, threads_dead, &args_dead);
}

void	manage_threads(t_philo *philos, t_sim *sim)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sim->num_of_philo * sizeof(pthread_t));
	if (!threads)
		return ;
	create_threads(sim, philos, threads);
	while (i < sim->num_of_philo)
		pthread_join(threads[i++], NULL);
}
