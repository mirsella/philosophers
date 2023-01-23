/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:22:30 by lgillard          #+#    #+#             */
/*   Updated: 2023/01/23 11:17:10 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

void	*philo(void *void_philo)
{
	t_philo	*p;

	p = (t_philo *)void_philo;
	if (p->id % 2)
		usleep(10000);
	while (p->rules->exit == 0)
	{
		pthread_mutex_lock(p->left_fork);
		ft_putinfo(*p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
		ft_putinfo(*p, "has taken a fork");
		if (p->rules->exit)
			break ;
		ft_putinfo(*p, "is eating");
		usleep_check_exit(p->rules, p->rules->time_to_eat);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		p->last_eat = get_time();
		p->nb_eat++;
		if (p->rules->exit)
			break ;
		ft_putinfo(*p, "is sleeping");
		usleep_check_exit(p->rules, p->rules->time_to_sleep);
	}
	return (NULL);
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
		if (data->rules.nb_min_eat != -1)
			while (i < data->rules.nb_philo
				&& data->philos[i].nb_eat >= data->rules.nb_min_eat)
				i++;
		if (i == data->rules.nb_philo)
			data->rules.exit = 1;
	}
}

int	start_threads(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	data->rules.start_time = get_time();
	while (i < data->rules.nb_philo)
	{
		data->philos[i].last_eat = data->rules.start_time;
		ret = pthread_create(&data->philos[i].thread, NULL,
				&philo, &data->philos[i]);
		if (ret < 0)
		{
			data->rules.exit = 1;
			close_threads(data);
			free_mutexes(data);
			return (ret);
		}
		i++;
	}
	printf("started %d threads in %lld ms\n", data->rules.nb_philo,
		get_time() - data->rules.start_time);
	check_eat(data);
	close_threads(data);
	free_mutexes(data);
	return (0);
}
