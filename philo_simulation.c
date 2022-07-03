/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:39:13 by tyamagis          #+#    #+#             */
/*   Updated: 2022/07/03 19:35:20 by tyamagis         ###   ########.fr       */
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
	while (gettimeofday(&(stat->time_sim_start), NULL) != 0)
		;
	printf("%lu sim start.\n", current_timestamp(stat));
	philos_begin_sim(stat);
	while (!is_dead(stat) && (stat->num_eat == -1 || !is_full(stat)))
		;
	destruct_sim(stat);
	return ;
}
