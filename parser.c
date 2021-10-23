/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:11:43 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/10/23 12:11:56 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
