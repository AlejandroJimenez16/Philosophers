/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:58:21 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/30 16:46:53 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*philo_routine(void *arg)
{
	t_args	*args;
	t_philo	*philo;
	t_sim	*sim;

	args = (t_args *)arg;
	philo = args->philo;
	sim = args->sim;
	while (!sim->someone_dead && !sim->all_saciated)
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
			sim->all_saciated = 1;
			return (1);
		}
	}
	return (0);
}

static void	*threads_dead(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	while (1)
	{
		i = -1;
		while (++i < sim->num_of_philo)
		{
			if (get_time_ms(sim) >= sim->philos[i].last_meal + sim->time_die)
			{
				pthread_mutex_lock(&sim->print_mutex);
				if (!sim->someone_dead)
				{
					sim->someone_dead = 1;
					printf("\033[31m%lld [%d] %s\033[0m\n", get_time_ms(sim),
						sim->philos[i].id, "died");
				}
				return (pthread_mutex_unlock(&sim->print_mutex), NULL);
			}
		}
		if (check_num_meals(sim))
			return (NULL);
		usleep(1000);
	}
}

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
