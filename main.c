/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:03:41 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/10/23 12:15:34 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo		*philos;
	pthread_t	*threads;
	int			i;

	if (argc != 5 && argc != 6)
	{
		printf("Error:\nWrong number of arguments\n");
		return (1);
	}
	if (manage_args(argv))
		return (1);
	else
		philos = init_philos(argc, argv);
	if (!philos)
		return (1);
	threads = malloc(sizeof(pthread_t) * philos->data->num_philos);
	i = -1;
	while (++i < philos->data->num_philos)
		pthread_mutex_init(&philos->data->forks[i], NULL);
	if (philo(philos, threads) == 0)
		return (0);
}
