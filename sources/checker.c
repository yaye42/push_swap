/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:42:05 by yaye              #+#    #+#             */
/*   Updated: 2019/12/03 13:42:06 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "push_swap.h"

void	end_leave(t_ps *env)
{
	t_card	*p;

	while (env->a)
	{
		p = (env->a)->next;
		ft_bzero(env->a, sizeof(*env->a));
		ft_memdel((void **)&env->a);
		env->a = p;
	}
	while (env->b)
	{
		p = (env->b)->next;
		ft_bzero(env->b, sizeof(*env->b));
		ft_memdel((void **)&env->b);
		env->b = p;
	}
	ft_bzero(env, sizeof(*env));
}

int		main(int ac, char **av)
{
	t_ps	env;
	char	*buf;
	int		gnl;

	if (ac < 1 || !boot(ac, av, &env))
		return (EXIT_FAILURE);
	printlist(&env);
	while ((gnl = get_next_line(0, &buf)) > 0)
	{
		env.error = 1;
		operate(&env, buf);
		ft_memdel((void **)&buf);
		if (env.error)
			leave(&env.a, &env.b, "\n");
		printlist(&env);
	}
	if (gnl == -1)
		leave(&env.a, &env.b, ": failed to read on STANDARD INPUT.\n");
	write(1, (is_asce_sorted(env.a) == 2 && !env.b) ? "OK\n" : "KO\n", 3);
	end_leave(&env);
	return (EXIT_SUCCESS);
}
