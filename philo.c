/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:19:04 by tyamagis          #+#    #+#             */
/*   Updated: 2022/07/04 22:42:04 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_resources(t_stat *stat)
{
	int	i;

	i = 0;
	printf("DESTROY!\n");
	while (i < stat->num_philo)
	{
		if (pthread_mutex_destroy(&stat->fork[i]) != 0)
			printf("destroy err\n");
		i++;
	}
	if (stat->philo != NULL)
		free(stat->philo);
	if (stat->fork != NULL)
		free(stat->fork);
}

void	destruct_sim(t_stat * stat)
{
	int	i;

	i = 0;
	stat->time_to_die = 2147483647;
	stat->time_to_eat = 0;
	stat->time_to_sleep = 2147483647;
	while (i < stat->num_philo)
	{
		stat->philo[i].state = WAITING;
		i++;
	}
}

static bool	valid_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (false);
	i = 0;
	while (++i < ac)
	{
		if (philo_isnum(av[i]) == false)
			return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_stat	stat;

	if (valid_args(ac, av) == false)
		return (print_err(ERR_ARGS));
	if (inits(&stat, ac, av) == false)
	{
		free_resources(&stat);
		return (print_err(ERR_STATS));
	}
	simulation(&stat);
	sleep(1);
	destruct_sim(&stat);
	free_resources(&stat);
	fflush(stdout);
	return (0);
}
