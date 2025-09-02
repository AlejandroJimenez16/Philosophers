/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:57:06 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/02 13:02:03 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_sim
{
	int	num_of_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_times_eat;
}		t_sim;

// Utils
int		ft_atoi(const char *str);
void	show_error_args(void);

#endif