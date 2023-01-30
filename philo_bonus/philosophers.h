/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:51:43 by mirsella          #+#    #+#             */
/*   Updated: 2023/01/30 19:49:05 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h> // for threads
# include <unistd.h> // for usleep
# include <semaphore.h> // for sem_*
# include <fcntl.h> // for O_* constants
# include <sys/stat.h> // for mode constants
# include <string.h> // for memset
# include <sys/time.h> // for gettimeofday
# include <sys/wait.h> // for waitpid
# include <stdlib.h> // for exit

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
	int			id;
	pid_t		pid;
	int			nb_eat;
	long long	last_eat;
	pthread_t	thread;
	sem_t		*forks;
	sem_t		*writing;
	t_rules		*rules;
}				t_philo;

typedef struct s_data
{
	t_rules	rules;
	t_philo	philos[MAX_PHILO];
	sem_t	*forks;
	sem_t	*writing;
}				t_data;

int			parse_args(int ac, char **av, t_data *data);
int			start_threads(t_data *data);
int			ft_pos_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
long long	get_time(void);
void		ft_putinfo(t_philo philo, char *str);
int			usleep_check_exit(t_rules *rules, long long time);
void		free_semaphores(t_data *data);
void		close_threads(t_data *data);

#endif
