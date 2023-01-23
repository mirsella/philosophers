/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:51:43 by mirsella          #+#    #+#             */
/*   Updated: 2023/01/23 11:21:47 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdio.h"
# include "stdlib.h"
# include <pthread.h>
# include <unistd.h>
# include <string.h>

# include <sys/time.h>

# define MAX_PHILO 250

typedef struct s_rules
{
	int				nb_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_min_eat;
	int				exit;
	long long		start_time;
}				t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				nb_eat;
	long long		last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*writing;
	pthread_mutex_t	*check_eat;
	t_rules			*rules;
}				t_philo;

typedef struct s_data
{
	t_rules			rules;
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];
	pthread_mutex_t	writing;
	pthread_mutex_t	check_death;
}				t_data;

int			parse_args(int ac, char **av, t_data *data);
int			start_threads(t_data *data);
int			ft_pos_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
long long	get_time(void);
void		ft_putinfo(t_philo philo, char *str);
int			usleep_check_exit(t_rules *rules, long long time);
void		free_mutexes(t_data *data);
void		close_threads(t_data *data);

#endif
