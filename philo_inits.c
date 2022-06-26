/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:13:59 by tyamagis          #+#    #+#             */
/*   Updated: 2022/06/26 22:19:26 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	valid_stats(t_stat *stat, int ac)
{
	if (stat->num_philo < 0
		|| stat->time_to_die < 0
		|| stat->time_to_eat < 0
		|| stat->time_to_sleep < 0
		|| (stat->num_eat < 0 && ac == 6))
	{
		return (false);
	}
	return (true);
}

static t_philo	*init_philos(t_stat *stat)
{
	int		i;
	t_philo	*philo;

	stat->info_philo = (t_philo *)malloc(sizeof(t_philo) * stat->num_philo);
	if (stat->info_philo == NULL)
		return (NULL);
	i = 0;
	while (i < stat->num_philo)
	{
		philo = &(stat->info_philo[i]);
		philo->id = i;
		philo->state = WAITING;
		philo->num_ate = 0;
		philo->time_from_eat = 0;
		if (pthread_create(&(philo->tid), NULL, &philosophy, philo) != 0)
			return (NULL);
		printf("init_philos() create philo[%d]\n", i);
		i++;
	}
	return (stat->info_philo);
}

static bool	init_mtx_forks(t_stat *stat)
{
	int	i;
	stat->fork = (t_mtx *)malloc(sizeof(t_mtx) * stat->num_philo);
	if (stat->fork == NULL)
		return (false);
	i = 0;
	while (i < stat->num_philo)
	{
		if (pthread_mutex_init(&(stat->fork[i]), NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

static bool	init_stats(t_stat *stat, int ac, char **av)
{
	stat->num_philo = philo_atoi(av[1]);
	stat->time_to_die = philo_atoi(av[2]);
	stat->time_to_eat = philo_atoi(av[3]);
	stat->time_to_sleep = philo_atoi(av[4]);
	stat->num_eat = -1;
	if (ac == 6)
		stat->num_eat = philo_atoi(av[5]);
	if (init_mtx_forks(stat) == false)
		return (false);
	stat->msg[0] = MSG_TAKE;
	stat->msg[1] = MSG_EAT;
	stat->msg[2] = MSG_SLEEP;
	stat->msg[3] = MSG_THINK;
	stat->msg[4] = MSG_STARVE;
	return (true);
}

bool	inits(t_stat *stat, int ac, char **av)
{
	if (init_stats(stat, ac, av) == false || valid_stats(stat, ac) == false)
		return (false);
	stat->info_philo = init_philos(stat);
	if (stat->info_philo == NULL)
		return (false);
	return (true);
}
