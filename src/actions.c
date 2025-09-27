/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:28:53 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/28 01:11:05 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void eat_action(t_philo *philo, t_sim *sim)
{
	if (sim->num_of_philo == 1)
	{
    	pthread_mutex_lock(&philo->left_fork->fork);
    	print_status(sim, philo->id, "has taken a fork");
    	smart_usleep(sim, sim->time_die);
    	pthread_mutex_unlock(&philo->left_fork->fork);
    	return;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		if (!sim->someone_dead)
			print_status(sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork);
		if (!sim->someone_dead)
			print_status(sim, philo->id, "has taken a fork");
	}
	else
	{
    	pthread_mutex_lock(&philo->right_fork->fork);
		if (!sim->someone_dead)
    		print_status(sim, philo->id, "has taken a fork");
    	pthread_mutex_lock(&philo->left_fork->fork);
		if (!sim->someone_dead)
    		print_status(sim, philo->id, "has taken a fork");
	}
	if (!sim->someone_dead)
		print_status(sim, philo->id, "is eating");
	philo->last_meal = get_time_ms(sim);
	philo->num_meals++;
	smart_usleep(sim, sim->time_eat);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void    sleep_action(t_philo *philo, t_sim *sim)
{
	if (!sim->someone_dead)
		print_status(sim, philo->id, "is sleeping");
	smart_usleep(sim, sim->time_sleep);
}

void    think_action(t_philo *philo, t_sim *sim)
{
	if (!sim->someone_dead)
		print_status(sim, philo->id, "is thinking");
}