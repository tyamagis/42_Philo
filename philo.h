/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamagis <tyamagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:38:26 by tyamagis          #+#    #+#             */
/*   Updated: 2022/06/27 21:28:29 by tyamagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// includes
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

// error messages
# define ERR_ARGS "Error >> invalid argument.\n"
# define ERR_STATS "Error >> illegal value in arguments.\n"

enum e_stat {TAKE, EAT, SLEEP, THINK, STARVE, WAITING};

# define MSG_TAKE " has taken a fork"
# define MSG_EAT " is eating"
# define MSG_SLEEP " is sleeping"
# define MSG_THINK " is thinking"
# define MSG_STARVE " died"

// usage string
# define USAGE "\n\
Usage\t./philo [0] [1] [2] [3] [option]\n\
	\n\
	[0]\tnumber of philosophers\n\
	[1]\ttime to die\n\
	[2]\ttime to eat\n\
	[3]\ttime to sleep\n\
	[option]\tnumber of times each must eat\n\
	\n\
arguments must be POSITIVE and less than or equal to the INT_MAX number.\n\
\n\
if [option] specified, \n\
program will stops when all philos have eaten the specified meals.\n\n"

typedef pthread_mutex_t	t_mtx;
typedef struct timeval	t_tv;

typedef struct s_philo {
	int				id;
	pthread_t		tid;
	int				state;
	int				num_ate;
	t_tv			time_prev_meal;
	struct s_stat	*info;
}	t_philo;

typedef struct s_stat {
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_eat;
	t_tv	time_sim_start;
	t_philo	*philo;
	t_mtx	*fork;
	char	*msg[5];
}	t_stat;

// Prototypes
// utils
int		philo_atoi(char *s);
bool	philo_isnum(char *s);
int		print_err(char *msg);

// inits
bool	inits(t_stat *stat, int ac, char **av);

void	simulation(t_stat *stat);
void	*philosophy(void *arg);
void	destruct_sim(t_stat *stat);

#endif