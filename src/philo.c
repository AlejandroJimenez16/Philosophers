/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:06:15 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/04 21:52:17 by alejandj         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	t_sim	sim;

	if (argc == 5 || argc == 6)
	{
		init_data(&sim, argc, argv);

		// Creo los forks
		t_fork	left;
		pthread_mutex_init(&left.fork, NULL);

		t_fork right;
		pthread_mutex_init(&right.fork, NULL);
		
		//Creo el filosofo
		t_philo philo;
		philo.id = 1;
		philo.left_fork = &left;
		philo.right_fork = &right;
		philo.num_meals = 0;

		// Inicializo los args de la funciom
		t_args	args;
		args.philo = &philo;
		args.sim = &sim;

		// Creo el hilo
		pthread_t	thread_philo;
		pthread_create(&thread_philo, NULL, philo_routine, &args);
		pthread_join(thread_philo, NULL);
		return (0);
	}
	else
	{
		show_error_args();
		return (1);
	}
}
