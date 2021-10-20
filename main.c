/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:03:41 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/10/20 18:46:21 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	return ((c > 47) && (c < 58));
}

int	validate_data(t_data *data)
{
	if (data->num_philos <= 0)
		return (1);
	if (data->ttl <= 0)
		return (1);
	if (data->tte <= 0)
		return (1);
	if (data->tts <= 0)
		return (1);
	if ((data->is_tme == 1) && data->tme <= 0)
		return (1);
	return (0);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;
	int		i;

	data = (t_data*)malloc(sizeof(t_data));
	data->num_philos = atoi(argv[1]);
	data->ttl = atoi(argv[2]);
	data->tte = atoi(argv[3]);
	data->tts = atoi(argv[4]);
	if (argc == 6)
	{
		data->tme = atoi(argv[5]);
		data->is_tme = 1;
	}
	else
	{
		data->tme = 0;
		data->is_tme = 0;
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	return (data);
}

t_philo	*init_philos(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

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
	}
	return (philo);
}

int	manage_args(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Argument is not digit\n");
				return (1);
			}
		}
	}
	return (0);
}

unsigned int	get_time(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec / 1000) + (now.tv_usec *1000));
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	if (pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->num_philos]) == 0)
	{
		pthread_mutex_lock(&philo->data->mutex);
		printf("%u %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->mutex);
	}
	/* eating */
	pthread_mutex_lock(&philo->data->mutex);
	printf("%u %d is eating\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->mutex);
	usleep(philo->data->tte * 1000);
	/* sleeping */
	pthread_mutex_lock(&philo->data->mutex);
	printf("%u %d is sleeping\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->mutex);
	usleep(philo->data->tts * 1000);
	/* thinking */
	pthread_mutex_lock(&philo->data->mutex);
	printf("%u %d is thinking\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->mutex);
	/* unlocking fork */
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	pthread_mutex_unlock(&philo->data->forks[philo->id + 1]);

	return (NULL);
}

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
	pthread_mutex_init(&philos->data->mutex, NULL);
	i = -1;
	while (++i < philos->data->num_philos)
	{
		pthread_create(&threads[i], NULL, &routine, &philos[i]);
	}
	i = -1;
	while (++i < philos->data->num_philos)
	{
		pthread_join(threads[i], NULL);
	}
	pthread_mutex_destroy(&philos->data->mutex);
}
