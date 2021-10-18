/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:03:41 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/10/18 14:04:57 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	init_data(int argc, char **argv)
{
	t_data data;

	data.philos = atoi(argv[1]);
	data.ttl = atoi(argv[2]);
	data.tte = atoi(argv[3]);
	data.tts = atoi(argv[4]);
	if (argc == 6)
		data.tme = argv[5];
	else
		data.tme = -1;
	return (data);
}

int	manage_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (!isdigit(argv[i]))
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments");
		return (1);
	}
	if (manage_args(argv))
		return(1);
	else
		data = init_data(argc, argv);
}