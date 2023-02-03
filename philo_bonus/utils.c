/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:18:16 by lgillard          #+#    #+#             */
/*   Updated: 2023/02/03 15:33:57 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <semaphore.h>
#include <sys/time.h>

int	ft_pos_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	if (!str || !str[0])
		return (-1);
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * neg);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	isalive(t_philo *philo)
{
	if (philo->died)
		return (0);
	if (get_time() - philo->last_eat > philo->rules->time_to_die)
	{
		philo->died = 1;
		sem_wait(philo->writing);
		printf("%lld %d died", get_time() - philo->rules->start_time,
			philo->id);
		return (0);
	}
	return (1);
}

void	ft_putinfo(t_philo philo, char *str)
{
	sem_wait(philo.writing);
	printf("%lld %d %s\n", get_time() - philo.rules->start_time, philo.id, str);
	sem_post(philo.writing);
}

void	usleep_check_alive(t_philo *p, long long time)
{
	long long	start;

	start = get_time();
	while (isalive(p))
	{
		if (get_time() - start >= time)
			break ;
		usleep(50);
	}
}
