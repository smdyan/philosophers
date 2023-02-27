/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:16:21 by smdyan            #+#    #+#             */
/*   Updated: 2022/05/31 17:11:00 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_par	*arg_set;

	arg_set = set_arg(argc, argv);
	if (!arg_set)
		return (-1);
	life_run(arg_set);
	life_dwn(arg_set);
	return (0);
}

int	e_msg(char *str)
{
	printf("Error: %s\n", str);
	return (-1);
}

void	prnt_msg(const char *txt, long tv, int id, pthread_mutex_t *p_lock)
{
	pthread_mutex_lock(p_lock);
	printf("%ld %d %s\n", tv, id, txt);
	pthread_mutex_unlock(p_lock);
}
