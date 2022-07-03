/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:39:13 by tyamagis          #+#    #+#             */
/*   Updated: 2022/07/03 23:25:30 by tyamagis         ###   ########.fr       */
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

bool	is_dead_or_full(t_stat *stat)
{
	int	i;
	int	satisfied;

	i = 0;
	satisfied = 0;
	while (i < stat->num_philo)
	{
		if (stat->philo[i].state == STARVE)
			return (true);
		if (stat->num_eat != -1 && stat->philo[i].num_ate >= stat->num_eat)
			satisfied++;
		i++;
	}
	if (satisfied == stat->num_philo)
		return (true);
	return (false);
}

void	simulation(t_stat *stat)
{
	while (gettimeofday(&(stat->time_sim_start), NULL) != 0)
		;
	philos_begin_sim(stat);
	while (is_dead_or_full(stat) == false)
		;
	printf(DEATH_ANNOUNCE);
	return ;
}
