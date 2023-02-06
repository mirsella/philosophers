/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:35:06 by mirsella          #+#    #+#             */
/*   Updated: 2023/02/06 11:23:32 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	kill_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.nb_philo)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}

void	free_semaphores(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->writing);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_writing");
}

void	handle_exit(t_data *data)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (i < data->rules.nb_philo)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			kill_process(data);
			break ;
		}
		i++;
	}
	free_semaphores(data);
}
