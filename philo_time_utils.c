/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:50:34 by tyamagis          #+#    #+#             */
/*   Updated: 2022/06/28 21:32:01 by tyamagis         ###   ########.fr       */
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
