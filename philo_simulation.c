/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:39:13 by tyamagis          #+#    #+#             */
/*   Updated: 2022/07/04 22:43:52 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_begin_sim(t_stat *stat)
{
	int	i;

	i = 0;
	while (i < stat->num_philo)
	{
		stat->philo[i].state = THINK;
		i++;
	}
	return ;
}

void	simulation(t_stat *stat)
{
	while (gettimeofday(&(stat->time_sim_start), NULL) != 0)
		;
	philos_begin_sim(stat);
	while (stat->sim_ends != stat->num_philo)
		;
	return ;
}
