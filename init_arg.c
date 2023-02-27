/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:21:27 by smdyan            #+#    #+#             */
/*   Updated: 2022/05/31 15:51:16 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_default(t_par *arg)
{
	arg->id = 0;
	arg->n_phs = 0;
	arg->n_eat = -1;
	arg->alive = 1;
	return (0);
}

int	check(int a, int b, int c, int d)
{
	if (a < 0 || b < 0 || c < 0 || d < 0)
		return (-1);
	return (0);
}

t_par	pars_arg(int argc, char **argv)
{
	t_par	arg;
	int		i;
	int		f;

	set_default(&arg);
	i = 0;
	if (argc == 5 || argc == 6)
	{
		arg.n_phs = ft_atoi(*(argv + ++i));
		arg.t_die = ft_atoi(*(argv + ++i));
		arg.t_eat = ft_atoi(*(argv + ++i));
		arg.t_slp = ft_atoi(*(argv + ++i));
		if (argc == 6)
			arg.n_eat = ft_atoi(*(argv + ++i));
		f = check(arg.n_phs, arg.t_die, arg.t_eat, arg.t_slp);
	}
	else
		f = -1;
	if (f == -1)
	{
		arg.n_phs = 0;
		printf("Error: n_phs t_die t_eat t_slp n_eat \n");
		return (arg);
	}
	return (arg);
}

t_par	*set_arg(int argc, char **argv)
{
	t_par	*arg_set;
	t_par	param;
	int		idx;

	param = pars_arg(argc, argv);
	arg_set = (t_par *)malloc(sizeof (t_par) * (param.n_phs + 1));
	if (arg_set == 0)
	{
		printf("Error: memory fault\n");
		free(param.phs_set);
		free(param.fkl_set);
		return (NULL);
	}
	if (!frk_init(&param) && !phs_init(&param) && param.n_phs)
		*(param.sim_on) = 1;
	*arg_set = param;
	idx = 0;
	while (idx < param.n_phs)
	{
		param.id = param.id + 1;
		*(arg_set + idx) = param;
		idx++;
	}
	return (arg_set);
}
