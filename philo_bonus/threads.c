/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:22:30 by lgillard          #+#    #+#             */
/*   Updated: 2023/01/26 15:34:14 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/types.h>
#include <unistd.h>

// void	philo_eat(t_philo *p)
// {
// 	pthread_mutex_lock(p->left_fork);
// 	if (p->rules->exit)
// 	{
// 		pthread_mutex_unlock(p->left_fork);
// 		return ;
// 	}
// 	ft_putinfo(*p, "has taken a fork");
// 	pthread_mutex_lock(p->right_fork);
// 	if (p->rules->exit)
// 	{
// 		pthread_mutex_unlock(p->left_fork);
// 		pthread_mutex_unlock(p->right_fork);
// 		return ;
// 	}
// 	ft_putinfo(*p, "has taken a fork");
// 	ft_putinfo(*p, "is eating");
// 	usleep_check_exit(p->rules, p->rules->time_to_eat);
// 	pthread_mutex_unlock(p->left_fork);
// 	pthread_mutex_unlock(p->right_fork);
// 	p->last_eat = get_time();
// 	p->nb_eat++;
// }

void	philo(t_philo *p)
{
	printf("philo %d, pid %d, at %lld\n", p->id, getpid(), get_time() - p->rules->start_time);
	if (p->id % 2)
		usleep(10000);
	// while (!p->rules->exit)
	// {
		// philo_eat(p);
		// if (p->rules->exit)
		// 	break ;
		// ft_putinfo(*p, "is sleeping");
		// usleep_check_exit(p->rules, p->rules->time_to_sleep);
	// }
}

void	check_eat(t_data *data)
{
	int	i;

	while (!data->rules.exit)
	{
		i = 0;
		while (i < data->rules.nb_philo && !data->rules.exit)
		{
			if (get_time() - data->philos[i].last_eat > data->rules.time_to_die)
			{
				data->rules.exit = 1;
				ft_putinfo(data->philos[i], "died");
			}
			i++;
		}
		if (data->rules.exit)
			break ;
		i = 0;
		while (data->rules.nb_min_eat != -1 && i < data->rules.nb_philo
				&& data->philos[i].nb_eat >= data->rules.nb_min_eat)
			i++;
		if (i == data->rules.nb_philo)
			data->rules.exit = 1;
	}
}

int	start_threads(t_data *data)
{
	int		i;
	pid_t	ret;

	i = 0;
	data->rules.start_time = get_time();
	while (i < data->rules.nb_philo)
	{
		ret = fork();
		if (ret == 0)
			philo(&data->philos[i]);
		else if (ret > 0)
			data->philos[i].pid = ret;
		else if (ret < 0)
		{
			data->rules.exit = 1;
			printf("Error: fork failed\n");
			free_semaphores(data);
			return (0);
		}
		i++;
	}
	check_eat(data);
	free_semaphores(data);
	return (1);
}
