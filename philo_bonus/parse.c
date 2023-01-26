/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:15:10 by lgillard          #+#    #+#             */
/*   Updated: 2023/01/26 15:45:20 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_semaphores(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/writing");
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU, data->rules.nb_philo);
	data->forks = sem_open("/writing", O_CREAT, S_IRWXU, 1);
	if (data->forks == SEM_FAILED || data->writing == SEM_FAILED)
		return (1);
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.nb_philo)
	{
		data->philos[i].id = i;
		data->philos[i].nb_eat = 0;
		data->philos[i].last_eat = 0;
		data->philos[i].rules = &data->rules;
		data->philos[i].writing = data->writing;
		data->philos[i].forks = data->forks;
		i++;
	}
}

int	parse_args(int ac, char **av, t_data *data)
{
	data->rules.nb_min_eat = -1;
	data->rules.nb_philo = ft_pos_atoi(av[1]);
	data->rules.time_to_die = ft_pos_atoi(av[2]);
	data->rules.time_to_eat = ft_pos_atoi(av[3]);
	data->rules.time_to_sleep = ft_pos_atoi(av[4]);
	if (ac == 6)
		data->rules.nb_min_eat = ft_pos_atoi(av[5]);
	if (data->rules.nb_philo < 2 || data->rules.nb_philo > 250
		|| data->rules.time_to_die < 0 || data->rules.time_to_eat < 0
		|| data->rules.time_to_sleep < 0
		|| (data->rules.nb_min_eat < 1 && ac == 6))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (init_semaphores(data))
	{
		printf("Error: sem_open failed\n");
		free_semaphores(data);
		return (1);
	}
	init_philos(data);
	return (0);
}
