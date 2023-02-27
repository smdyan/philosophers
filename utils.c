/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:00:02 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/01 21:31:23 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		dig;
	long	res;

	dig = 0;
	res = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v'
		|| *str == ' ' || *str == '\r' || *str == '\f')
		str++;
	while (*str == '0')
		str++;
	while ((*str >= '0') && (*str <= '9'))
	{
		res = res * 10 + (*str - '0');
		dig++;
		if (dig > 10 || res > INT_MAX)
			return (e_msg("Bad parameter"));
		str++;
	}
	if (dig == 0)
		return (e_msg("Bad parameter"));
	return ((int)res);
}

long	t_interval(struct timeval tv1, struct timeval tv2)
{
	long	sec;
	long	msec;

	sec = tv2.tv_sec - tv1.tv_sec;
	msec = (sec * 1000 + tv2.tv_usec / 1000) - tv1.tv_usec / 1000;
	return (msec);
}

long	t_curt(struct timeval tv_srt)
{
	long			sec;
	long			msec;
	struct timeval	tv2;

	gettimeofday(&tv2, NULL);
	sec = tv2.tv_sec - tv_srt.tv_sec;
	msec = (sec * 1000 + tv2.tv_usec / 1000) - tv_srt.tv_usec / 1000;
	return (msec);
}

void	ft_usleep(int us)
{
	struct timeval	t1;
	struct timeval	t2;

	gettimeofday(&t1, NULL);
	gettimeofday(&t2, NULL);
	while ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec - t1.tv_usec < us)
	{
		usleep(10);
		gettimeofday(&t2, NULL);
	}
}

void	choose_frk(t_par *cfg, int *idx1, int *idx2)
{
	*idx1 = cfg->id - 1;
	*idx2 = cfg->id;
	if (cfg->id == cfg->n_phs)
	{
		*idx2 = *idx1;
		*idx1 = 0;
	}
}
