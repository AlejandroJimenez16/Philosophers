/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:28:53 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/25 15:46:27 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void eat_action(t_philo *philo, t_sim *sim)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		print_status(sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork);
		print_status(sim, philo->id, "has taken a fork");
	}
	else
	{
    	pthread_mutex_lock(&philo->right_fork->fork);
    	print_status(sim, philo->id, "has taken a fork");
    	pthread_mutex_lock(&philo->left_fork->fork);
    	print_status(sim, philo->id, "has taken a fork");
	}
	print_status(sim, philo->id, "is eating");
	philo->last_meal = get_time_ms(sim);
	philo->num_meals++;
	usleep(sim->time_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void    sleep_action(t_philo *philo, t_sim *sim)
{
    print_status(sim, philo->id, "is sleeping");
    usleep(sim->time_sleep * 1000);
}

void    think_action(t_philo *philo, t_sim *sim)
{
    print_status(sim, philo->id, "is thinking");
}