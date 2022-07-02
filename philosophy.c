/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:33:45 by tyamagis          #+#    #+#             */
/*   Updated: 2022/07/02 22:25:07 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: considering too many calls ? measure actual time later.

#include "philo.h"

// first,
// odd ided philo try to take his LEFT fork.
// even ided philo try to take his RIGHT fork.
// if success then, try opposite too.
// fail then, give up first fork.
bool	is_fork_available(t_philo *p_stat)
{
	int		i;
	int		mtx_ret;
	t_stat	*stat;

	stat = p_stat->info;
	i = p_stat->id - !(p_stat->id & 1);
	if (i == -1)
		i = stat->num_philo - 1;
		
	mtx_ret = pthread_mutex_lock(&stat->fork[i]);
	if (mtx_ret != 0)
		return (false);
		
	i = p_stat->id - (p_stat->id & 1);
	
	mtx_ret = pthread_mutex_lock(&stat->fork[i]);
	if (mtx_ret != 0)
	{
		while (pthread_mutex_lock(&stat->fork[i]) != 0)
			;
		return (false);
	}
	return (true);
}

bool	is_time_elapsed(t_philo *p_stat)
{
	t_stat			*stat;
	unsigned long	time_elapsed;

	stat = p_stat->info;
	if (p_stat->state == STARVE)
		return (false);
	time_elapsed = current_timestamp(stat) - p_stat->time_prev_meal;
	if (time_elapsed >= stat->time_to_die)
	{
		p_stat->state = STARVE;
		print_state(p_stat);
		return (false);
	}
	if (p_stat->state == EAT)
	{
		if (time_elapsed < stat->time_to_eat)
			return (false);
	}
	else if (p_stat->state == SLEEP)
	{
		if (time_elapsed < (stat->time_to_eat + stat->time_to_sleep))
			return (false);
	}
	return (true);
}

void	eat_to_live(t_philo *p_stat)
{
	if (is_fork_available(p_stat))
	{
		p_stat->state = EAT;
		p_stat->time_prev_meal = current_timestamp(p_stat->info);
		print_state(p_stat);
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
		else if (is_time_elapsed(p_stat))
		{
			p_stat->state++;
			print_state(p_stat);
		}
		else
			usleep(TURN_IN); // TODO: adjust turn-in time usleep uses.
	}
	return (NULL);
}
