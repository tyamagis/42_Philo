/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:51:30 by tyamagis          #+#    #+#             */
/*   Updated: 2022/06/26 21:34:05 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_atoi(char *s)
{
	int	n;
	int check_n;

	n = 0;
	while (*s != '\0')
	{
		check_n = n;
		n *= 10;
		if (n / 10 != check_n)
			return (-1);
		check_n = n;
		n += *s - '0';
		if (n < check_n)
			return (-1);
		s++;
	}
	return (n);
}

bool	philo_isnum(char *s)
{
	while (*s != '\0')
	{
		if (!(*s >= '0' && *s <= '9'))
			return (false);
		s++;
	}
	return (true);
}

int	print_err(char *msg)
{
	printf(msg);
	printf(USAGE);
	return (EXIT_FAILURE);
}

void	print_stats(t_stat *stat, t_tv current_time, int i, int act)
{
	unsigned long	timestamp;

	timestamp = (current_time.tv_usec - stat->time_sim_start.tv_usec) / 1000;
	timestamp += (current_time.tv_sec - stat->time_sim_start.tv_sec) * 1000;
	printf("%lu %d %s\n", timestamp, i, stat->msg[act]);
}