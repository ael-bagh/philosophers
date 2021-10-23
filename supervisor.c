/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:13:26 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/10/23 12:14:38 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	done_eating(t_philo *philos)
{
	int	i;
	int	is_tme;

	is_tme = philos->data->is_tme;
	i = -1;
	while (++i < philos->data->num_philos)
	{
		if (is_tme == 0)
			return (-1);
		if (is_tme == 1 && philos[i].eating_times < philos->data->tme)
			return (0);
	}
	return (1);
}

int	supervisor(t_philo *philos)
{
	int	i;

	i = -1;
	if (done_eating(philos) == 1)
	{
		pthread_mutex_lock(&philos->data->mutex);
		printf("done eating\n");
		free(philos->data);
		free(philos);
		return (0);
	}
	while (++i < philos->data->num_philos)
	{
		if ((get_time() - philos[i].time_started_eating) >= philos->data->ttl
			&& philos[i].is_eating == 0)
		{
			pthread_mutex_lock(&philos->data->mutex);
			printf("%lld %d died", timestamp(philos), philos[i].id);
			free(philos->data);
			free(philos);
			return (0);
		}
	}
	return (1);
}
