/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 01:20:53 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/01 18:56:13 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	hld_frk(t_par *cfg);
void	act_eat(t_par *cfg);
void	act_slp(t_par *cfg);
void	act_thk(t_par *cfg);

void	*f_action(void *arg)
{
	t_par	*cfg;

	cfg = (t_par *)arg;
	if (cfg->id % 2)
		ft_usleep(1050);
	else
		ft_usleep(1200);
	while (*(cfg->sim_on) && cfg->alive)
	{
		hld_frk(cfg);
		act_slp(cfg);
		act_thk(cfg);
	}
	return (NULL);
}

void	hld_frk(t_par *cfg)
{
	int	idx1;
	int	idx2;

	if (*(cfg->sim_on) && cfg->alive)
	{
		choose_frk(cfg, &idx1, &idx2);
		pthread_mutex_lock(cfg->fkl_set + idx1);
		prnt_msg("has taken a fork", t_curt(cfg->tv_srt), cfg->id, cfg->p_lck);
		if (cfg->n_phs == 1)
		{
			pthread_mutex_unlock(cfg->fkl_set + idx1);
			ft_usleep((cfg->t_die + 2) * 1000);
			return ;
		}
		pthread_mutex_lock(cfg->fkl_set + idx2);
		prnt_msg("has taken a fork", t_curt(cfg->tv_srt), cfg->id, cfg->p_lck);
		act_eat(cfg);
		pthread_mutex_unlock(cfg->fkl_set + idx2);
		ft_usleep(900);
		pthread_mutex_unlock(cfg->fkl_set + idx1);
	}
}

void	act_eat(t_par *cfg)
{
	if (*(cfg->sim_on) && cfg->alive)
	{
		prnt_msg("is eating", t_curt(cfg->tv_srt), cfg->id, cfg->p_lck);
		pthread_mutex_lock(cfg->a_lock);
		gettimeofday(&cfg->tv_eat, NULL);
		if (cfg->n_eat > 0)
			cfg->n_eat -= 1;
		if (cfg->n_eat == 0)
			cfg->alive = 0;
		pthread_mutex_unlock(cfg->a_lock);
		ft_usleep(cfg->t_eat * 1000);
	}
}

void	act_slp(t_par *cfg)
{
	if (*(cfg->sim_on) && cfg->alive)
	{
		prnt_msg("is sleeping", t_curt(cfg->tv_srt), cfg->id, cfg->p_lck);
		ft_usleep(cfg->t_slp * 1000);
	}
}

void	act_thk(t_par *cfg)
{
	if (*(cfg->sim_on) && cfg->alive)
		prnt_msg("is thinking", t_curt(cfg->tv_srt), cfg->id, cfg->p_lck);
}
