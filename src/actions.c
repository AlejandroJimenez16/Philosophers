/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:28:53 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/04 21:51:29 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void eat_action(t_philo *philo, t_sim *sim)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	printf("%lld %s%d%s\n", get_time_ms(sim), "[", philo->id, "] has taken a fork");
	pthread_mutex_lock(&philo->right_fork->fork);
	printf("%lld %s%d%s\n", get_time_ms(sim), "[", philo->id, "] has taken a fork");
	printf("%lld %s%d%s\n", get_time_ms(sim), "[", philo->id, "] is eating");
	usleep(sim->time_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void    sleep_action(t_philo *philo, t_sim *sim)
{
    printf("%lld %s%d%s\n", get_time_ms(sim), "[", philo->id, "] is sleeping");
    usleep(sim->time_sleep * 1000);
}

void    think_action(t_philo *philo, t_sim *sim)
{
    printf("%lld %s%d%s\n", get_time_ms(sim), "[", philo->id, "]  is thinking");
}