/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:06:15 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/28 23:22:05 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	init_data(t_sim *sim, int argc, char *argv[])
{
	sim->num_of_philo = ft_atol(argv[1]);
	sim->time_die = ft_atol(argv[2]);
	sim->time_eat = ft_atol(argv[3]);
	sim->time_sleep = ft_atol(argv[4]);
	if (argc == 6)
		sim->num_times_eat = ft_atol(argv[5]);
	else
		sim->num_times_eat = -1;
	gettimeofday(&sim->start_time, NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
	sim->someone_dead = 0;
	sim->all_saciated = 0;
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

int	main(int argc, char *argv[])
{
	t_sim		sim;

	if (argc == 5 || argc == 6)
	{
		if (check_args(argc, argv) == 0)
			exit (1);
		init_data(&sim, argc, argv);
		sim.philos = malloc(sim.num_of_philo * sizeof(t_philo));
		if (!sim.philos)
			return (1);
		sim.forks = malloc(sim.num_of_philo * sizeof(t_fork));
		if (!sim.forks)
			return (1);
		fill_forks(sim.forks, sim.num_of_philo);
		fill_philos(sim.philos, sim.forks, sim.num_of_philo);
		manage_threads(&sim);
		clean_up(&sim);
	}
	else
		show_error_args();
	return (0);
}
