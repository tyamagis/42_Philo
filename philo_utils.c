/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:51:30 by tyamagis          #+#    #+#             */
/*   Updated: 2022/07/03 19:56:31 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	current_timestamp(t_stat *stat)
{
	unsigned long	ms;
	t_tv			tv;

	while (gettimeofday(&tv, NULL) != 0)
		;
	ms = (tv.tv_usec - stat->time_sim_start.tv_usec) / 1000;
	ms += (tv.tv_sec - stat->time_sim_start.tv_sec) * 1000;
	return (ms);
}

int	philo_atoi(char *s)
{
	int	n;
	int	check_n;

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

void	print_state(t_philo *p_stat, unsigned long ts)
{
	int		id;
	char	*msg;

	id = p_stat->id + 1;
	msg = p_stat->info->msg[p_stat->state];
	printf("%8lu %d %s\n", ts, id, msg);
}