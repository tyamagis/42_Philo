/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:33:45 by tyamagis          #+#    #+#             */
/*   Updated: 2022/07/04 00:12:03 by tyamagis         ###   ########.fr       */
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
	int		primal_i;
	int		second_i;
	int		mtx_ret;
	t_stat	*stat;

	stat = p_stat->info;
	primal_i = p_stat->id - !(p_stat->id & 1);
	if (primal_i == -1)
		primal_i = stat->num_philo - 1;
	mtx_ret = pthread_mutex_lock(&stat->fork[primal_i]);
	if (mtx_ret != 0)
		return (false);
	second_i = p_stat->id - (p_stat->id & 1);
	mtx_ret = pthread_mutex_lock(&stat->fork[second_i]);
	if (mtx_ret != 0)
	{
		while (pthread_mutex_unlock(&stat->fork[primal_i]) != 0)
			;
		return (false);
	}
	return (true);
}

void	put_fork(t_philo *p_stat)
{
	int		li;
	int		ri;
	t_stat	*st;

	li = p_stat->id;
	ri = p_stat->id - 1;
	st = p_stat->info;
	if (ri == -1)
		ri = p_stat->info->num_philo - 1;
	while (pthread_mutex_unlock(&st->fork[li]) != 0)
		;
	while (pthread_mutex_unlock(&st->fork[ri]) != 0)
		;
}

bool	is_time_elapsed(t_philo *p_stat, unsigned long crnt)
{
	t_stat			*st;
	unsigned long	time_elpsd;

	st = p_stat->info;
	if (p_stat->state == WAITING || p_stat->state == STARVE)
		return (false);
	time_elpsd = crnt - p_stat->time_prev_meal;
	if (time_elpsd >= (unsigned long)st->time_to_die)
	{
		if (p_stat->state == EAT)
			put_fork(p_stat);
		p_stat->state = STARVE;
		print_state(p_stat, crnt);
		return (false);
	}
	if (p_stat->state == EAT)
	{
		if (time_elpsd < (unsigned long)st->time_to_eat)
			return (false);
		put_fork(p_stat);
	}
	else if (p_stat->state == SLEEP)
	{
		if (time_elpsd < (unsigned long)(st->time_to_eat + st->time_to_sleep))
			return (false);
	}
	return (true);
}

void	eat_to_live(t_philo *p_stat)
{
	unsigned long	ts;

	if (is_fork_available(p_stat))
	{
		ts = current_timestamp(p_stat->info);
		p_stat->state = TAKE;
		print_state(p_stat, ts);
		p_stat->state = EAT;
		p_stat->time_prev_meal = ts;
		p_stat->num_ate++;
		print_state(p_stat, ts);
	}
}

void	*philosophy(void *arg)
{
	t_philo			*p_stat;
	unsigned long	crnt_time;

	p_stat = (t_philo *)arg;
	while (p_stat->state != STARVE)
	{
		crnt_time = current_timestamp(p_stat->info);
		if (p_stat->state == THINK)
			eat_to_live(p_stat);
		else if (is_time_elapsed(p_stat, crnt_time))
		{
			p_stat->state++;
			print_state(p_stat, crnt_time);
		}
		else
			usleep(TURN_IN);
	}
	return (NULL);
}
