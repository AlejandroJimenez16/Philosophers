/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:58:21 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/28 00:42:23 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_args *args = (t_args *)arg;
	t_philo *philo = args->philo;
	t_sim *sim = args->sim;

	while (!sim->someone_dead)
	{
		eat_action(philo, sim);
		sleep_action(philo, sim);
		think_action(philo, sim);
	}
	return (NULL);
}

void	*threads_dead(void *arg)
{
	t_sim	*sim = (t_sim *)arg;
	int		i;

	while (1)
	{
		i = 0;
		while(i < sim->num_of_philo)
		{
			if (get_time_ms(sim) >= sim->philos[i].last_meal + sim->time_die)
			{
				pthread_mutex_lock(&sim->print_mutex);
				printf("\033[31m%lld [%d] %s\033[0m\n", get_time_ms(sim), sim->philos[i].id, "died");
				pthread_mutex_unlock(&sim->print_mutex);
				sim->someone_dead = 1;
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	create_threads(t_sim *sim)
{
	t_args		*args;
	int	i;

	args = malloc(sim->num_of_philo * sizeof(t_args));
	if (!args)
		return ;
	i = 0;
	while (i < sim->num_of_philo)
	{
		args[i].philo = &sim->philos[i];
		args[i].sim = sim;
		pthread_create(&sim->threads[i], NULL, philo_routine, &args[i]);
		i++;
	}
	pthread_create(&sim->dead_thread, NULL, threads_dead, sim);
}

void	manage_threads(t_sim *sim)
{
	int			i;

	i = 0;
	sim->threads = malloc(sim->num_of_philo * sizeof(pthread_t));
	if (!sim->threads)
		return ;
	create_threads(sim);
	while (i < sim->num_of_philo)
	{
		pthread_join(sim->threads[i], NULL);
		i++;
	}
	pthread_join(sim->dead_thread, NULL);
}
