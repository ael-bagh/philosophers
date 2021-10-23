/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:03:51 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/10/23 12:22:49 by ael-bagh         ###   ########.fr       */
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
	int								num_philos;
	unsigned long long				ttl;
	unsigned long long				tte;
	unsigned long long				tts;
	int								is_tme;
	int								tme;
	unsigned long long				program_start;
	pthread_mutex_t					mutex;
	pthread_mutex_t					*forks;
}				t_data;

typedef struct s_philo {
	int						id;
	unsigned long long		time_started_eating;
	int						eating_times;
	int						is_eating;
	pthread_mutex_t			eating;
	t_data					*data;
}				t_philo;

unsigned long long	get_time(void);
void				wesleep(unsigned long long time);
unsigned long long	timestamp(t_philo *philo);
t_data				*init_data(int argc, char **argv);
t_philo				*init_philos(int argc, char **argv);
int					ft_isdigit(int c);
int					ft_atoi(const char *ptr);
int					validate_data(t_data *data);
int					manage_args(char **argv);
int					done_eating(t_philo *philos);
int					supervisor(t_philo *philos);
void				locking_forks(t_philo *philo, int id);
void				unlocking_forks(t_philo *philo, int id);
void				dining_table(t_philo *philo, int id);
void				*routine(void *arg);
int					philo(t_philo *philos, pthread_t *threads);

#endif
