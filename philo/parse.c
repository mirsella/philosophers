/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:15:10 by lgillard          #+#    #+#             */
/*   Updated: 2023/01/23 11:22:09 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		if (&data->forks[i] == NULL)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->writing, NULL))
		return (0);
	if (pthread_mutex_init(&data->check_death, NULL))
		return (0);
	return (1);
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
		data->philos[i].writing = &data->writing;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1)
			% data->rules.nb_philo];
		i++;
	}
}

int	parse_args(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 6)
		return (0);
	data->rules.nb_philo = ft_pos_atoi(av[1]);
	data->rules.time_to_die = ft_pos_atoi(av[2]);
	data->rules.time_to_eat = ft_pos_atoi(av[3]);
	data->rules.time_to_sleep = ft_pos_atoi(av[4]);
	if (ac == 6)
		data->rules.nb_min_eat = ft_pos_atoi(av[5]);
	if (data->rules.nb_philo < 2 || data->rules.nb_philo > 250
		|| data->rules.time_to_die < 0 || data->rules.time_to_eat < 0
		|| data->rules.time_to_sleep < 0 || data->rules.nb_min_eat < 0)
		return (-1);
	if (ac != 6)
		data->rules.nb_min_eat = -1;
	if (!init_mutex(data))
	{
		printf("Error: mutex init failed\n");
		free_mutexes(data);
		return (-2);
	}
	init_philos(data);
	return (1);
}
