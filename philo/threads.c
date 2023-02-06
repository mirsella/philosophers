/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:22:30 by lgillard          #+#    #+#             */
/*   Updated: 2023/02/06 10:25:59 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

int	philo_eat(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	if (!isexit(p->rules))
		ft_putinfo(*p, "has taken a fork");
	if (isexit(p->rules) || p->left_fork == p->right_fork)
	{
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	pthread_mutex_lock(p->right_fork);
	if (isexit(p->rules))
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		return (1);
	}
	ft_putinfo(*p, "has taken a fork");
	p->last_eat = get_time();
	ft_putinfo(*p, "is eating");
	usleep_check_exit(p->rules, p->rules->time_to_eat);
	incrementnb_eat(p);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	if (isexit(p->rules))
		return (1);
	return (0);
}

void	*philo(void *void_philo)
{
	t_philo	*p;

	p = (t_philo *)void_philo;
	if (p->id % 2)
		usleep(10000);
	while (!isexit(p->rules))
	{
		if (philo_eat(p))
			break ;
		ft_putinfo(*p, "is sleeping");
		usleep_check_exit(p->rules, p->rules->time_to_sleep);
	}
	return (NULL);
}

void	check_eat(t_data *data)
{
	int	i;

	while (!isexit(&data->rules))
	{
		i = 0;
		while (i < data->rules.nb_philo && !isexit(&data->rules))
		{
			if (get_time() - data->philos[i].last_eat > data->rules.time_to_die)
			{
				setexit(&data->rules, 1);
				ft_putinfo(data->philos[i], "died");
			}
			i++;
		}
		if (isexit(&data->rules))
			break ;
		i = 0;
		while (data->rules.nb_min_eat != -1 && i < data->rules.nb_philo
			&& getnb_eat(&data->philos[i]) >= data->rules.nb_min_eat)
			i++;
		if (i == data->rules.nb_philo)
			setexit(&data->rules, 1);
	}
}

int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	data->rules.start_time = get_time();
	while (i < data->rules.nb_philo)
	{
		data->philos[i].last_eat = data->rules.start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo, &data->philos[i]))
		{
			setexit(&data->rules, 1);
			printf("Error: pthread_create failed\n");
			close_threads(data);
			free_mutexes(data);
			return (0);
		}
		i++;
	}
	check_eat(data);
	close_threads(data);
	free_mutexes(data);
	return (1);
}
