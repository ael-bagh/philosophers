/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:08:42 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/10/23 12:09:31 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;
	int		i;

	data = (t_data *)malloc(sizeof(t_data));
	data->num_philos = atoi(argv[1]);
	data->ttl = atoi(argv[2]);
	data->tte = atoi(argv[3]);
	data->tts = atoi(argv[4]);
	data->tme = 0;
	data->is_tme = 0;
	if (argc == 6)
	{
		data->tme = atoi(argv[5]);
		data->is_tme = 1;
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	pthread_mutex_init(&data->mutex, NULL);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	return (data);
}

t_philo	*init_philos(int argc, char **argv)
{
	t_philo			*philo;
	t_data			*data;
	int				i;
	struct timeval	now;

	gettimeofday(&now, NULL);
	data = init_data(argc, argv);
	if (validate_data(data))
	{
		printf("Error:\nOne or many arguments is 0 or Negative\n");
		return (NULL);
	}
	philo = malloc(sizeof(t_philo) * data->num_philos);
	i = -1;
	while (++i < data->num_philos)
	{
		philo[i].id = i;
		philo[i].data = data;
		philo[i].time_started_eating = get_time();
		philo[i].eating_times = 0;
		philo[i].is_eating = 0;
		pthread_mutex_init(&philo[i].eating, NULL);
	}
	return (philo);
}
