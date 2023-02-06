/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:57:00 by lgillard          #+#    #+#             */
/*   Updated: 2023/02/06 09:41:51 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	isexit(t_rules *rules)
{
	pthread_mutex_lock(&rules->exit_check);
	if (rules->exit)
	{
		pthread_mutex_unlock(&rules->exit_check);
		return (1);
	}
	pthread_mutex_unlock(&rules->exit_check);
	return (0);
}

int	setexit(t_rules *rules, int value)
{
	pthread_mutex_lock(&rules->exit_check);
	rules->exit = value;
	pthread_mutex_unlock(&rules->exit_check);
	return (0);
}

int	incrementnb_eat(t_philo *p)
{
	pthread_mutex_lock(p->nb_eat_mutex);
	p->nb_eat++;
	pthread_mutex_unlock(p->nb_eat_mutex);
	return (0);
}

int	getnb_eat(t_philo *p)
{
	int	value;

	pthread_mutex_lock(p->nb_eat_mutex);
	value = p->nb_eat;
	pthread_mutex_unlock(p->nb_eat_mutex);
	return (value);
}
