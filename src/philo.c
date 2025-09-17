/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:06:15 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/17 18:28:22 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(t_sim *sim, int argc, char *argv[])
{
	sim->num_of_philo = ft_atoi(argv[1]);
	sim->time_die = ft_atoi(argv[2]);
	sim->time_eat = ft_atoi(argv[3]);
	sim->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->num_times_eat = ft_atoi(argv[5]);
	else
		sim->num_times_eat = -1;
	gettimeofday(&sim->start_time, NULL);
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
		i++;
	}
}

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

void	manage_threads(t_philo *philos, t_sim *sim)
{
	pthread_t	*threads;
	t_args		*args;
	int 		i;

	threads = malloc(sim->num_of_philo * sizeof(pthread_t));
	if (!threads)
		return ;
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
	i = 0;
	while (i < sim->num_of_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	
}

int	main(int argc, char *argv[])
{
	t_sim		sim;
	t_philo		*philos;
	t_fork		*forks;
	

	if (argc == 5 || argc == 6)
	{
		// Guardo info simulacion
		init_data(&sim, argc, argv);

		// Creo los arrays 
		philos = malloc(sim.num_of_philo * sizeof(t_philo));
		if (!philos)
			return (1);
		forks = malloc(sim.num_of_philo * sizeof(t_fork));
		if (!forks)
			return (1);

		// Lleno los arrays
		fill_forks(forks, sim.num_of_philo);
		fill_philos(philos, forks, sim.num_of_philo);

		//------------------------------------------------------------------------------------------------
		
		// Ver si la info es correcta
		for (int i = 0; i < sim.num_of_philo; i++)
		{
			printf("Philo: %d\n", philos[i].id);
			printf("Left fork: %d\n", philos[i].left_fork->fork_id);
			printf("right fork: %d\n", philos[i].right_fork->fork_id);
			printf("\n");
		}
		//-------------------------------------------------------------------------------------------------
		
		manage_threads(philos, &sim);
		
		/*
		// Creo el hilo
		pthread_t	thread_philo;
		pthread_create(&thread_philo, NULL, philo_routine, &args);
		pthread_join(thread_philo, NULL);
		return (0);
		*/
	}
	else
	{
		show_error_args();
		return (1);
	}
}
