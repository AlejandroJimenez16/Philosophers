/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:06:15 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/29 17:41:54 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_args(int argc, char *argv[])
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

static void	init_data(t_sim *sim, int argc, char *argv[])
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

static int	validate_init_args(int argc, char *argv[], t_sim *sim)
{
	if (check_args(argc, argv) == 0)
	{
		printf("\033[31mError: all arguments must be "
			"positive integers greater than 0.\033[0m\n");
		return (1);
	}
	init_data(sim, argc, argv);
	if (sim->num_of_philo == 0)
	{
		printf("\033[31mError: number of philosophers "
			"must be at least 1.\033[0m\n");
		return (1);
	}
	if (sim->time_die == 0 || sim->time_eat == 0 || sim->time_sleep == 0)
	{
		printf("\033[31mError: all arguments must be "
			"positive integers greater than 0.\033[0m\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_sim		sim;

	if (argc == 5 || argc == 6)
	{
		if (validate_init_args(argc, argv, &sim))
			return (1);
		sim.philos = malloc(sim.num_of_philo * sizeof(t_philo));
		if (!sim.philos)
			return (1);
		sim.forks = malloc(sim.num_of_philo * sizeof(t_fork));
		if (!sim.forks)
			return (free(sim.philos), 1);
		fill_forks(sim.forks, sim.num_of_philo);
		fill_philos(sim.philos, sim.forks, sim.num_of_philo);
		manage_threads(&sim);
		clean_up(&sim);
	}
	else
		show_error_args();
	return (0);
}
