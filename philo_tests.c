/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:00:07 by tyamagis          #+#    #+#             */
/*   Updated: 2022/06/26 22:10:41 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_inits(t_stat *stat)
{
	printf("num_philo : %d\ntime_to_die : %d\n", stat->num_philo, stat->time_to_die);
	printf("time_to_eat : %d\ntime_to_sleep : %d\n", stat->time_to_eat, stat->time_to_sleep);
	printf("num_eat : %d\n", stat->num_eat);
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
		return (print_err(ERR_STATS));

	print_inits(&stat);
}