/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:33:45 by tyamagis          #+#    #+#             */
/*   Updated: 2022/07/02 19:54:05 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: considering too many calls ? measure actual time later.

#include "philo.h"

bool	is_fork_available()
{
	
}

bool	is_starve()
{
	
}

bool	is_time_elapsed(t_stat *stat, t_philo *p_stat, enum state)
{
	unsigned long	time_elapsed;

	if (state == STARVE)
		return (false);
	time_elapsed = current_timestamp(stat) - p_stat->time_prev_meal;
	if (state == EAT)
	{
		if (time_elapsed < stat->time_to_eat)
			return (false);
	}
	else if (state == SLEEP)
	{
		if (time_elapsed < (stat->time_to_eat + stat->time_to_sleep))
			return (false);
	}
	return (true);
}

void	eat_to_live(t_philo *p_stat)
{
	if (is_fork_available())
	{
		// fork lock
		// and roll...
	}
}

void	*philosophy(void *arg)
{
	t_philo	*p_stat;

	p_stat = (t_philo *)arg;
	while (p_stat->state != STARVE)
	{
		if (p_stat->state == THINK)
			eat_to_live(p_stat);
		else if (is_time_elapsed(p_stat->state)) // EAT, SLEEP, STARVE
			p_stat->state++;
		else
			usleep(TURN_IN); // TODO: adjust turn-in time usleep uses.
	}
	return (NULL);
}

// 哲学者の行動
// 考える
// 	フォークを見る
// 	→　両方とれるなら取る
// 	→　両方とれないなら考えとく　→　フォークを見る
// 	フォークが両方取れたら食う
// 		time_to_eat の間、フォークを保持
// 	食い終わったら寝る
// 		time_to_eat の間、フォークを保持し終わったら、time_to_sleep の間寝る
// 	time_from_eat が time_to_death を超えたら死ぬ。

