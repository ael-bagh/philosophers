/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:15:10 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/10/23 12:23:49 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	locking_forks(t_philo *philo, int id)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->id]) == 0)
	{
		pthread_mutex_lock(&philo->data->mutex);
		printf("%lld %d has taken a fork\n", timestamp(philo), philo->id);
		pthread_mutex_unlock(&philo->data->mutex);
	}
	if (pthread_mutex_lock(&philo->data->forks[id]) == 0)
	{
		pthread_mutex_lock(&philo->data->mutex);
		printf("%lld %d has taken a fork\n", timestamp(philo), philo->id);
		pthread_mutex_unlock(&philo->data->mutex);
	}
}

void	unlocking_forks(t_philo *philo, int id)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	pthread_mutex_unlock(&philo->data->forks[id]);
}

void	dining_table(t_philo *philo, int id)
{
	locking_forks(philo, id);
	pthread_mutex_lock(&philo[philo->id].eating);
	pthread_mutex_lock(&philo->data->mutex);
	printf("%lld %d is eating\n", timestamp(philo), philo->id);
	pthread_mutex_unlock(&philo->data->mutex);
	philo->time_started_eating = get_time();
	philo->is_eating = 1;
	wesleep(philo->data->tte);
	philo->is_eating = 0;
	unlocking_forks(philo, id);
	pthread_mutex_unlock(&philo[philo->id].eating);
	philo->eating_times++;
	pthread_mutex_lock(&philo->data->mutex);
	printf("%lld %d is sleeping\n", timestamp(philo), philo->id);
	pthread_mutex_unlock(&philo->data->mutex);
	wesleep(philo->data->tts);
	pthread_mutex_lock(&philo->data->mutex);
	printf("%lld %d is thinking\n", timestamp(philo), philo->id);
	pthread_mutex_unlock(&philo->data->mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		id;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(100);
	id = (philo->id + 1) % philo->data->num_philos;
	philo->time_started_eating = get_time();
	while (1)
		dining_table(philo, id);
	return (NULL);
}

int	philo(t_philo *philos, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < philos->data->num_philos)
	{
		if (i == 0)
			philos[0].data->program_start = get_time();
		pthread_create(&threads[i], NULL, &routine, &philos[i]);
	}
	while (1)
	{
		if (supervisor(philos) == 0)
		{
			free(threads);
			return (0);
		}
	}
	return (1);
}
