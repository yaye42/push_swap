/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:14:51 by yaye              #+#    #+#             */
/*   Updated: 2020/01/15 12:14:53 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "push_swap.h"

void	leave(t_card **carda, t_card **cardb, char *msg)
{
	t_card	*p;

	while (*carda)
	{
		p = (*carda)->next;
		ft_bzero(*carda, sizeof(**carda));
		ft_memdel((void **)carda);
		*carda = p;
	}
	while (*cardb)
	{
		p = (*cardb)->next;
		ft_bzero(*cardb, sizeof(**cardb));
		ft_memdel((void **)cardb);
		*cardb = p;
	}
	write(2, "Error", 5);
	if (msg)
		write(2, msg, ft_strlen(msg));
	else
		write(2, "\n", 1);
	exit(1);
}

/*
** RETURNS 1: CARDS SORTED ON THE WHEEL
** RETURNS 2: END CONDITION FOR PUSH_SWAP
*/

int		is_asce_sorted(t_card *card)
{
	t_card	*p;

	p = card;
	while (p && p->next)
	{
		if (p->value > p->next->value)
		{
			p = p->next;
			while (p->next)
			{
				if (p->value > p->next->value)
					return (0);
				p = p->next;
			}
			if (p->value > card->value)
				return (0);
			return (1);
		}
		p = p->next;
	}
	return (2);
}

/*
** Check if x exists in env->a
** Return 0 if it exists
** Return 1 and add a t_card with value == x in last position of env->a
*/

int		unique(t_ps *env, int x)
{
	t_card *p;

	if (env->a)
	{
		p = env->a;
		while (p->next)
			if (p->value == x || !(p = p->next))
				return (0);
		if (p->value == x || !(p->next = (t_card *)malloc(sizeof(t_card))))
			return (0);
		env->alast = p->next;
		env->alast->prev = p;
	}
	else
	{
		if (!(env->a = (t_card *)malloc(sizeof(t_card))))
			return (0);
		env->alast = env->a;
		env->alast->prev = NULL;
	}
	env->alast->value = x;
	env->alast->cplex = 0;
	env->alast->next = NULL;
	env->lena = env->lena + 1;
	return (1);
}

/*
** Check if str is a valable argument
** Then use unique() to check if its value is unique
** And add it to the end of env->a if so
*/

int		parsing(t_ps *env, char *str)
{
	int				i;
	int				l;
	int				n;

	i = 0;
	while (str[i])
	{
		if (!(l = ft_stoi(str + i, &n, '\t')) || !unique(env, n))
			return (0);
		i = i + l;
		while (str[i] && ft_isblanc(str[i]))
			i = i + 1;
	}
	return (1);
}

int		boot(int ac, char **av, t_ps *env)
{
	int		i;
	int		fd;
	t_card	*p;

	ft_bzero(env, sizeof(*env));
	if ((i = bonus(ac, av, env)) > ac)
		leave(&env->a, &env->b, "\n-r: |Values| <= 65536 & MAX - MIN >= n.\n");
	while (i < ac)
		if (!parsing(env, av[i++]))
			leave(&env->a, &env->b, ": not an int or duplicated element.\n");
	if (env->r && remove("ARGUMENTS") <= 0 \
		&& (fd = open("ARGUMENTS", O_WRONLY | O_APPEND | O_CREAT, 0666)) > 2)
	{
		p = env->a;
		while (p)
		{
			ft_putnbr_fd(p->value, fd);
			write(fd, (p->next) ? " " : "\n", 1);
			p = p->next;
		}
		close(fd);
	}
	return ((env->a) ? 1 : 0);
}
