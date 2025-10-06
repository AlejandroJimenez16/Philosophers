/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:28:53 by alejandj          #+#    #+#             */
/*   Updated: 2025/10/06 13:09:26 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	special_case(t_philo *philo, t_sim *sim)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	print_status(sim, philo->id, "\033[32mhas taken a fork\033[0m");
	smart_usleep(sim, sim->time_die);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

static void	take_forks(t_philo *philo, t_sim *sim)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		print_status(sim, philo->id, "\033[32mhas taken a fork\033[0m");
		pthread_mutex_lock(&philo->left_fork->fork);
		print_status(sim, philo->id, "\033[32mhas taken a fork\033[0m");
	}
	else
	{
		usleep(2000);
		pthread_mutex_lock(&philo->left_fork->fork);
		print_status(sim, philo->id, "\033[32mhas taken a fork\033[0m");
		pthread_mutex_lock(&philo->right_fork->fork);
		print_status(sim, philo->id, "\033[32mhas taken a fork\033[0m");
	}
}

void	eat_action(t_philo *philo, t_sim *sim)
{
	if (sim->num_of_philo == 1)
		return (special_case(philo, sim));
	take_forks(philo, sim);
	pthread_mutex_lock(&sim->death_mutex);
	philo->last_meal = get_time_ms(sim);
	pthread_mutex_unlock(&sim->death_mutex);
	print_status(sim, philo->id, "\033[33mis eating\033[0m");
	pthread_mutex_lock(&sim->death_mutex);
	philo->num_meals++;
	pthread_mutex_unlock(&sim->death_mutex);
	smart_usleep(sim, sim->time_eat);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	sleep_action(t_philo *philo, t_sim *sim)
{
	print_status(sim, philo->id, "\033[36mis sleeping\033[0m");
	smart_usleep(sim, sim->time_sleep);
}

void	think_action(t_philo *philo, t_sim *sim)
{
	print_status(sim, philo->id, "\033[35mis thinking\033[0m");
}
