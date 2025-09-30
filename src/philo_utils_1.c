/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:47:41 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/30 15:49:01 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atol(const char *str)
{
	int		i;
	long	result;
	int		sign;
	int		digit;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (sign == 1 && (result > (LONG_MAX - digit) / 10))
			return (LONG_MAX);
		if (sign == -1 && (-result < (LONG_MIN + digit) / 10))
			return (LONG_MIN);
		result = result * 10 + digit;
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long long	get_time_ms(t_sim *sim)
{
	long long		timestamp;
	struct timeval	now;

	gettimeofday(&now, NULL);
	timestamp = ((now.tv_sec - sim->start_time.tv_sec) * 1000LL)
		+ ((now.tv_usec - sim->start_time.tv_usec) / 1000);
	return (timestamp);
}

void	print_status(t_sim *sim, int id, const char *msg)
{
	pthread_mutex_lock(&sim->print_mutex);
	if (!sim->someone_dead && !sim->all_saciated)
		printf("%lld [%d] %s\n", get_time_ms(sim), id, msg);
	pthread_mutex_unlock(&sim->print_mutex);
}

void	show_error_args(void)
{
	printf("\033[0;31mINCORRECT ARGS\033[0m\n");
	printf("\033[0;33mExpected:\033[0m\n");
	printf("\033[0;33m  - Number of philosophers\033[0m\n");
	printf("\033[0;33m  - Time to die (ms)\033[0m\n");
	printf("\033[0;33m  - Time to eat (ms)\033[0m\n");
	printf("\033[0;33m  - Time to sleep (ms)\033[0m\n");
	printf("\033[0;33m  - Number times eat (OPTIONAL)\033[0m\n");
}
