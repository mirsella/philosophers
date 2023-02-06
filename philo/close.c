/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:00:18 by lgillard          #+#    #+#             */
/*   Updated: 2023/02/06 09:34:50 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->last_eat_mutex[i]);
		pthread_mutex_destroy(&data->nb_eat_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->exit_check);
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
