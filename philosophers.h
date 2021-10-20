/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:03:51 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/10/20 18:27:09 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
typedef struct s_data
{
	int				num_philos;
	int				ttl;
	int				tte;
	int				tts;
	int				is_tme;
	int				tme;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
}				t_data;

typedef struct s_philo {
	int				id;
	unsigned int	time_started_eating;
	t_data			*data;
}				t_philo;

#endif