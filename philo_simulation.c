/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:39:13 by tyamagis          #+#    #+#             */
/*   Updated: 2022/06/26 22:19:33 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophy(void *arg)
{
	t_philo	*p_stat;

	p_stat = (t_philo *)arg;
	while (42)
	{
		printf("i'm philo, %lu[%d].\n", p_stat->tid, p_stat->id);
		sleep(5);
	}
}

// 哲学者の行動
// 	フォークを見る
// 	→　両方とれるなら取る
// 	→　両方とれないなら考えとく　→　たまにフォークを見る
// 	フォークが両方取れたら食う
// 		time_to_eat の間、フォークを保持
// 	食い終わったら寝る
// 		time_to_eat の間、フォークを保持し終わったら、time_to_sleep の間寝る
// 	time_from_eat が time_to_death を超えたら死ぬ。

void	philos_begin_sim(t_stat *stat)
{
	int	i;

	i = 0;
	while (i < stat->num_philo)
	{
		stat->info_philo[i].state = THINK;
		i++;
	}
	return ;
}

bool	is_dead(t_stat *stat)
{
	if (stat != NULL){;}
	return (false);
}

bool	is_full(t_stat *stat)
{
	if (stat != NULL){;}
	return (false);
}
	
void	simulation(t_stat *stat)
{
	struct timezone	tz;

	while (gettimeofday(&(stat->time_sim_start), &tz) != 0)
		;
	philos_begin_sim(stat);
	while (!is_dead(stat) && (stat->num_eat == -1 || !is_full(stat)))
		;
	destruct_sim(stat);
	return ;
}
