/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:39:13 by tyamagis          #+#    #+#             */
/*   Updated: 2022/06/27 21:38:48 by tyamagis         ###   ########.fr       */
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

// こいつもスレッド立てて見守らせとくか？
// 関数呼び出しのコストがどれくらいのものか。
bool	is_dead(t_stat *stat)
{
	int	i;

	i = 0;
	while (i < stat->num_philo)
	{
		if (stat->philo[i].state == STARVE)
			return (true);
		i++;
	}
	return (false);
}

// こいつもスレッド立てて見守らせとくか？　２
bool	is_full(t_stat *stat)
{
	int	i;
	int	satisfied;

	i = 0;
	satisfied = 0;
	while (i < stat->num_philo)
	{
		if (stat->philo[i].num_ate >= stat->num_eat)
			satisfied++;
		i++;
	}
	if (satisfied == stat->num_philo)
		return (true);
	return (false);	
}
	
void	simulation(t_stat *stat)
{
	struct timezone	tz;

	while (gettimeofday(&(stat->time_sim_start), &tz) != 0)
		;
	printf("sim start.\n");
	philos_begin_sim(stat);
	while (!is_dead(stat) && (stat->num_eat == -1 || !is_full(stat)))
		;
	destruct_sim(stat);
	return ;
}
