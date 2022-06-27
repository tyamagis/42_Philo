/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:50:34 by tyamagis          #+#    #+#             */
/*   Updated: 2022/06/27 22:00:12 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ms timestamp

t_tv	current_timestamp()
{
	t_tv			tv;
	struct timezone	tz;

	while (gettimeofday(&tv, &tz) != 0)
		;
	return (tv);
}

unsigned long	time_to_ms(t_stat *stat, t_tv tv)
{
	unsigned long	ms;

	ms = (tv.usec - stat->time_sim_start.usec) / 1000;
	ms += (tv.sec - stat->time_sim_start.sec) * 1000;
	return (ms);
}