/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:22:30 by lgillard          #+#    #+#             */
/*   Updated: 2023/02/03 15:36:07 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/types.h>
#include <unistd.h>

int	sem_post_return(sem_t *sem)
{
	sem_post(sem);
	return (1);
}

int	philo_eat(t_philo *p)
{
	sem_wait(p->forks);
	ft_putinfo(*p, "has taken a fork");
	if (p->rules->nb_philo == 1)
	{
		sem_wait(p->writing);
		printf("%lld %d died", p->rules->time_to_die, p->id);
		return (sem_post_return(p->forks));
	}
	sem_wait(p->forks);
	if (!isalive(p))
	{
		sem_post(p->forks);
		sem_post(p->forks);
		return (1);
	}
	ft_putinfo(*p, "has taken a fork");
	p->last_eat = get_time();
	ft_putinfo(*p, "is eating");
	usleep_check_alive(p, p->rules->time_to_eat);
	p->nb_eat++;
	sem_post(p->forks);
	sem_post(p->forks);
	return (!isalive(p));
}

void	philo(t_philo *p)
{
	while (get_time() >= p->rules->start_time + 10)
		;
	p->last_eat = get_time();
	if (p->id % 2)
		usleep(10000);
	while (isalive(p))
	{
		if (philo_eat(p) || (p->rules->nb_min_eat != -1
				&& p->nb_eat >= p->rules->nb_min_eat))
			break ;
		ft_putinfo(*p, "is sleeping");
		usleep_check_alive(p, p->rules->time_to_sleep);
	}
	free_semaphores(&(t_data){.forks = p->forks, .writing = p->writing});
	if (!isalive(p))
		exit(1);
	exit(0);
}

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
			printf("Error: fork failed\n");
			kill_process(data);
			free_semaphores(data);
			return (1);
		}
		i++;
	}
	handle_exit(data);
	return (0);
}
