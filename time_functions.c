/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_funcions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:10:01 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/10/23 12:10:56 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

unsigned long long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	wesleep(unsigned long long time)
{
	unsigned long long	end;

	end = get_time() + time;
	while (get_time() < end)
		usleep(100);
}

unsigned long long	timestamp(t_philo *philo)
{
	return (get_time() - philo->data->program_start);
}
