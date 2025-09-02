/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:06:15 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/02 12:59:31 by alejandj         ###   ########.fr       */
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
}

int	main(int argc, char *argv[])
{
	t_sim	sim;

	if (argc == 5 || argc == 6)
	{
		init_data(&sim, argc, argv);
		printf("Numero Filosofos: %d\n", sim.num_of_philo);
		printf("Tiempo de muerte: %d\n", sim.time_die);
		printf("Tiempo de comer: %d\n", sim.time_eat);
		printf("Tiempo de dormir: %d\n", sim.time_sleep);
		printf("Numero de veces comer: %d\n", sim.num_times_eat);
		return (0);
	}
	else
	{
		show_error_args();
		return (1);
	}
}
