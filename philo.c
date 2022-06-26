/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:19:04 by tyamagis          #+#    #+#             */
/*   Updated: 2022/06/26 21:34:59 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destruct_sim(t_stat *stat)
{
	(void)stat;
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
	simulation(&stat);
	return (0);
}
