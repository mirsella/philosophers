/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:22:30 by lgillard          #+#    #+#             */
/*   Updated: 2023/01/20 17:33:57 by lgillard         ###   ########.fr       */
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
	while (p->rules->exit)
	{
		pthread_mutex_lock(p->left_fork);
		pthread_mutex_lock(p->right_fork);
		usleep_exit(p->rules, p->rules->time_to_eat);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		if (p->rules->exit)
			break ;
		usleep_exit(p->rules, p->rules->time_to_sleep);
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
				ft_putinfo(data, i, "died");
			}
			i++;
		}
		if (data->rules.exit)
			break ;
		i = 0;
		if (data->rules.nb_min_eat != -1)
			while (data->philos[i].nb_eat >= data->rules.nb_min_eat && i < data->rules.nb_philo)
				i++;
		if (i == data->rules.nb_philo)
			data->rules.exit = 1;
	}
}

void	close_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	start_threads(t_data *data)
{
	int i;

	i = 0;
	data->start_time = get_time();
	while (i < data->rules.nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo, &data->philos[i]))
		{
			close_threads(data);
			free_mutexes(data);
			return (0);
		}
		i++;
	}
	check_eat(data);
	close_threads(data);
	free_mutexes(data);
	return (0);
}
