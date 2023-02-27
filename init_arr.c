/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:25:24 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/01 12:01:45 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	frk_init(t_par *a)
{
	pthread_mutex_t	*fset;
	int				ok;
	int				i;

	fset = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * (a->n_phs + 2));
	if (fset == 0)
		return (e_msg("Memory fault"));
	i = 0;
	while (i < a->n_phs + 2)
	{
		ok = pthread_mutex_init(fset + i, NULL);
		if (ok != 0)
		{
			free(fset);
			return (e_msg("Creating mutex"));
		}
		i++;
	}
	a->fkl_set = fset;
	a->a_lock = fset + a->n_phs;
	a->p_lck = fset + a->n_phs + 1;
	return (0);
}

int	phs_init(t_par *arg)
{
	pthread_t	*phs_set;
	int			*sim_on;

	sim_on = (int *)malloc(sizeof (int));
	if (!sim_on)
	{
		free(arg->fkl_set);
		return (e_msg("Memory fault"));
	}
	*sim_on = 0;
	phs_set = (pthread_t *)malloc(sizeof (pthread_t) * arg->n_phs + 1);
	if (phs_set == 0)
	{
		free(sim_on);
		free(arg->fkl_set);
		return (e_msg("Memory fault"));
	}
	arg->phs_set = phs_set;
	arg->monitor_p = phs_set + arg->n_phs;
	arg->sim_on = sim_on;
	return (0);
}
