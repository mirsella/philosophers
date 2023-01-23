/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:00:18 by lgillard          #+#    #+#             */
/*   Updated: 2023/01/23 17:33:43 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_semaphores(t_data *data)
{
	sem_close(&data->forks);
	sem_close(&data->writing);
	sem_unlink("forks");
	sem_unlink("writing");
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
