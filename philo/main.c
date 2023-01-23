/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgillard <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:09:58 by lgillard          #+#    #+#             */
/*   Updated: 2023/01/23 13:48:17 by lgillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (ac < 5 || ac > 6)
	{
		printf("Error: invalid number of arguments\n");
		return (0);
	}
	if(parse_args(ac, av, &data))
		return (1);
	if (start_threads(&data))
		return (1);
	return (0);
}
