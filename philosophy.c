/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:33:45 by tyamagis          #+#    #+#             */
/*   Updated: 2022/06/27 21:59:56 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophy(void *arg)
{
	t_philo	*p_stat;

	p_stat = (t_philo *)arg;
	while (42)
	{
		if (p_stat->state == THINK && is_fork_available())
		{
			p_stat->state = EAT;
			p_stat->time_prev_meal = current_timestamp();
		}
		else if (p_stat->stte == EAT && is_time_elapsed(EAT))
		{
			p_stat->state = SLEEP;
		}
		else if (p_stat->state == SLEEP && is_time_elapsed(SLEEP))
		{
			p_stat->state = THINK;
		}
		if (current_timestamp() >= p_stat->info->time_to_die)
		{
			p_stat->state = STARVE;
		}
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

