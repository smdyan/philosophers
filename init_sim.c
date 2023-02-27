/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:25:24 by smdyan            #+#    #+#             */
/*   Updated: 2022/05/31 16:43:44 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	life_run(t_par *arg_set)
{
	int	i;
	int	ok;

	i = 0;
	while (i < arg_set->n_phs)
	{
		ok = pthread_create(arg_set->phs_set + i, NULL, f_action, arg_set + i);
		if (ok != 0)
			return (e_msg("Creating pthread"));
		ft_usleep(50);
		i++;
	}
	ok = pthread_create(arg_set->monitor_p, NULL, f_killer, arg_set);
	if (ok != 0)
		return (e_msg("Creating pthread"));
	return (0);
}

int	life_dwn(t_par *arg_set)
{
	int		ok;
	int		i;
	t_par	arg;

	i = 0;
	arg = *arg_set;
	while (i < arg.n_phs + 1)
	{
		ok = pthread_join(*(arg.phs_set + i++), NULL);
		if (ok != 0)
			return (e_msg("Joining pthread"));
	}
	i = 0;
	while (i < arg.n_phs + 2)
	{
		ok = pthread_mutex_destroy(arg.fkl_set + i++);
		if (ok != 0)
			return (e_msg("Mutex destroy"));
	}
	free(arg.fkl_set);
	free(arg.phs_set);
	free(arg.sim_on);
	free(arg_set);
	return (0);
}
