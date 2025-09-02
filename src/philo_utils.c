/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:47:41 by alejandj          #+#    #+#             */
/*   Updated: 2025/09/02 13:02:39 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
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
