/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:00:18 by lgillard          #+#    #+#             */
/*   Updated: 2023/02/03 08:40:19 by mirsella         ###   ########.fr       */
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
		i++;
	}
	pthread_mutex_destroy(&data->writing);
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
