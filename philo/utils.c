/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:18:16 by lgillard          #+#    #+#             */
/*   Updated: 2023/01/20 17:31:07 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
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

void	ft_putinfo(t_data *data, int i, char *s)
{
	pthread_mutex_lock(&data->writing);
	printf("%lld %d %s\n", get_time() - data->start_time, i, s);
	pthread_mutex_unlock(&data->writing);
}

int	usleep_exit(t_rules *rules, long long time)
{
	long long start;

	start = get_time();
	while (!rules->exit)
	{
		if (start - get_time() >= time)
			break ;
		usleep(50);
	}
	if (rules->exit)
		return (0);
	return (1);
}
