/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:22:30 by lgillard          #+#    #+#             */
/*   Updated: 2023/01/30 21:23:33 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/types.h>
#include <unistd.h>

void	*check_eat(void *void_philo)
{
	t_philo		*p;

	p = (t_philo *)void_philo;
	while (!p->rules->exit)
	{
		if (get_time() - p->last_eat > p->rules->time_to_die)
		{
			p->rules->exit = 1;
			ft_putinfo(*p, "died");
		}
		if (p->rules->nb_min_eat != -1 && p->nb_eat >= p->rules->nb_min_eat)
			break ;
	}
	return (NULL);
}

void	philo_eat(t_philo *p)
{
	sem_wait(p->forks);
	if (p->rules->exit)
	{
		sem_post(p->forks);
		return ;
	}
	ft_putinfo(*p, "has taken a fork");
	sem_wait(p->forks);
	if (p->rules->exit)
	{
		sem_post(p->forks);
		sem_post(p->forks);
		return ;
	}
	ft_putinfo(*p, "has taken a fork");
	ft_putinfo(*p, "is eating");
	usleep_check_exit(p->rules, p->rules->time_to_eat);
	sem_post(p->forks);
	sem_post(p->forks);
	p->last_eat = get_time();
	p->nb_eat++;
}

void	philo(t_philo *p)
{
	p->last_eat = get_time();
	if (p->id % 2)
		usleep(10000);
	pthread_create(&p->thread, NULL, check_eat, p);
	while (!p->rules->exit)
	{
		philo_eat(p);
		if (p->rules->exit || (p->rules->nb_min_eat != -1 && p->nb_eat >= p->rules->nb_min_eat))
			break ;
		ft_putinfo(*p, "is sleeping");
		usleep_check_exit(p->rules, p->rules->time_to_sleep);
	}
	pthread_join(p->thread, NULL);
	free_semaphores(&(t_data){.forks = p->forks, .writing = p->writing});
	if (p->rules->exit)
		exit(1);
	exit(0);
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
			i = 0;
			while (i < data->rules.nb_philo)
			{
				kill(data->philos[i].pid, SIGTERM);
				i++;
			}
			break ;
		}
		i++;
	}
	free_semaphores(data);
}

int	start_threads(t_data *data)
{
	int		i;

	i = 0;
	data->rules.start_time = get_time();
	while (i < data->rules.nb_philo)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			philo(&data->philos[i]);
			return (0);
		}
		else if (data->philos[i].pid < 0)
		{
			data->rules.exit = 1;
			printf("Error: fork failed\n");
			return (1);
		}
		// usleep(100);
		i++;
	}
	handle_exit(data);
	return (0);
}
