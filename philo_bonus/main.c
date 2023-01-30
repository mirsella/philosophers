/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:09:58 by lgillard          #+#    #+#             */
/*   Updated: 2023/01/30 21:30:55 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_semaphores(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->writing);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_writing");
}

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (ac < 5 || ac > 6)
	{
		printf("Error: invalid number of arguments\n");
		return (0);
	}
	if (parse_args(ac, av, &data))
		exit(1);
	if (start_threads(&data))
		exit(1);
	return (0);
}
