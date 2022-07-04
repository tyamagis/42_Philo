/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:33:45 by tyamagis          #+#    #+#             */
/*   Updated: 2022/07/04 22:40:14 by tyamagis         ###   ########.fr       */
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
	int		primal_fork;
	int		second_fork;
	int		mtx_ret;
	t_stat	*stat;

	stat = p_stat->info;
	primal_fork = p_stat->id - !(p_stat->id & 1);
	if (primal_fork == -1)
		primal_fork = stat->num_philo - 1;
	second_fork = p_stat->id - (p_stat->id & 1);
	mtx_ret = pthread_mutex_lock(&stat->fork[primal_fork]);
	if (mtx_ret != 0)
		return (false);
	printf("\tFORK <%d> locked\n", primal_fork);
	mtx_ret = pthread_mutex_lock(&stat->fork[second_fork]);
	if (mtx_ret != 0)
	{
		while (pthread_mutex_unlock(&stat->fork[primal_fork]) != 0)
			;
		printf("\tFORK <%d> locked\n", primal_fork);
		return (false);
	}
	printf("\tFORK <%d> locked\n", second_fork);
	return (true);
}

void	put_forks(t_philo *p_stat)
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
	printf("\tFORK <%d> UN - locked\n", li);
	while (pthread_mutex_unlock(&st->fork[ri]) != 0)
		;
	printf("\tFORK <%d> UN - locked\n", ri);
}

bool	is_time_elapsed(t_philo *p, unsigned long crnt)
{
	t_stat			*st;
	unsigned long	time_elpsd;
	unsigned long	time_to_do;

	if (p->state == WAITING || p->state == STARVE)
		return (false);
	st = p->info;
	time_elpsd = crnt - p->time_prev_meal;
	if (time_elpsd >= (unsigned long)st->time_to_die)
	{
		p->info->sim_end_flag = true;
		if (p->state == EAT)
			put_forks(p);
		p->state = STARVE;
		usleep(1000);
		print_state(p, crnt);
		return (false);
	}
	if (p->state == EAT)
		time_to_do = (unsigned long)st->time_to_eat;
	else if (p->state == SLEEP)
		time_to_do = (unsigned long)(st->time_to_eat + st->time_to_sleep);
	if (time_elpsd < time_to_do)
		return (false);
	return (true);
}

void	eat_to_live(t_philo *p_stat)
{
	unsigned long	ts;

	ts = current_timestamp(p_stat->info);
	p_stat->state = TAKE;
	print_state(p_stat, ts);
	p_stat->state = EAT;
	p_stat->time_prev_meal = ts;
	p_stat->num_ate++;
	print_state(p_stat, ts);
}

void	*philosophy(void *arg)
{
	t_philo			*p_stat;
	unsigned long	crnt_time;

	p_stat = (t_philo *)arg;
	while (p_stat->info->sim_end_flag == false)
	{
		crnt_time = current_timestamp(p_stat->info);
		if (p_stat->state == THINK && is_fork_available(p_stat))
			eat_to_live(p_stat);
		else if (is_time_elapsed(p_stat, crnt_time))
		{
			if (p_stat->state == EAT)
				put_forks(p_stat);
			p_stat->state++;
			print_state(p_stat, crnt_time);
		}
		else if (p_stat->state == STARVE)
			break;
		usleep(500);
	}
	if (p_stat->state == EAT)
		put_forks(p_stat);
	printf("th ends %d\n", p_stat->id);
	p_stat->info->sim_ends++;
	return (NULL);
}
