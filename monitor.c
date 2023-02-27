/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:16:04 by smdyan            #+#    #+#             */
/*   Updated: 2022/05/31 23:38:32 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct timeval	set_tv_srt(t_par *arg_set);
void			feedup(t_par *arg_set);

void	*f_killer(void *arg)
{
	long			die;
	int				i;
	t_par			*a_set;

	a_set = (t_par *)arg;
	set_tv_srt(a_set);
	while (*(a_set->sim_on))
	{
		i = 0;
		while (i < a_set->n_phs)
		{
			pthread_mutex_lock(a_set->a_lock);
			die = t_interval(a_set[i].tv_srt, a_set[i].tv_eat) + a_set[i].t_die;
			if (t_curt(a_set[i].tv_srt) >= die)
			{
				a_set[i].alive = 0;
				*(a_set[i].sim_on) = 0;
				prnt_msg("died", die, a_set[i].id, a_set[i].p_lck);
			}
			pthread_mutex_unlock(a_set->a_lock);
			i++;
		}
		feedup(a_set);
	}
	return (NULL);
}

void	feedup(t_par *arg_set)
{
	int		i;
	int		n;

	ft_usleep(500);
	i = 0;
	n = 0;
	pthread_mutex_lock(arg_set->a_lock);
	while (i < arg_set->n_phs && *(arg_set->sim_on))
	{
		n += arg_set[i].alive;
		i++;
	}
	if (n == 0)
		*(arg_set->sim_on) = 0;
	pthread_mutex_unlock(arg_set->a_lock);
}

struct timeval	set_tv_srt(t_par *arg_set)
{
	int				i;
	t_par			targ;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	i = 0;
	pthread_mutex_lock(arg_set->a_lock);
	while (i < arg_set->n_phs)
	{
		targ = arg_set[i];
		targ.tv_srt = tv;
		targ.tv_eat = tv;
		arg_set[i] = targ;
		i++;
	}
	pthread_mutex_unlock(arg_set->a_lock);
	return (tv);
}
