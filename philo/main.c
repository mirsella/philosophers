/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:09:58 by lgillard          #+#    #+#             */
/*   Updated: 2023/01/20 16:52:28 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
	t_data	data;
	int		ret;

	memset(&data, 0, sizeof(t_data));
	ret = parse_args(ac, av, &data);
	if (ret <= 0)
	{
		if (ret == 0)
			printf("Error: invalid number of arguments\n");
		else if (ret == -1)
			printf("Error: invalid arguments\n");
		else if (ret == -2)
			printf("Error: pthread_init_mutex failed\n");
		return (1);
	}
	ret = start_threads(&data);
	if (ret <= 0)
	{
		if (ret == 0)
			printf("Error: pthread_create failed");
	}
}
