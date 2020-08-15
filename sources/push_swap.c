/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:39:35 by yaye              #+#    #+#             */
/*   Updated: 2019/12/03 13:39:36 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "push_swap.h"

int		is_desc_sorted(t_card *card)
{
	t_card		*p;

	p = card;
	while (p && p->next)
	{
		if (p->value < p->next->value)
		{
			p = p->next;
			while (p->next)
			{
				if (p->value < p->next->value)
					return (0);
				p = p->next;
			}
			if (p->value < card->value)
				return (0);
			return (1);
		}
		p = p->next;
	}
	return (2);
}

void	end_sort(t_ps *env)
{
	if (!is_asce_sorted(env->a))
		execute(env, "sa");
	env->to_push = env->a;
	env->abcd[0] = 0;
	while (env->to_push && env->to_push->value != env->mina && ++env->abcd[0])
		env->to_push = env->to_push->next;
	while (is_asce_sorted(env->a) != 2)
		execute(env, (ft_igap(env->abcd[0] * 2, 0) <= env->lena) \
			? "ra" : "rra");
	env->to_push = env->b;
	env->abcd[0] = 0;
	while (env->to_push && env->to_push->value != env->maxb && ++env->abcd[0])
		env->to_push = env->to_push->next;
	while (is_desc_sorted(env->b) != 2)
		execute(env, (ft_igap(env->abcd[0] * 2, 0) <= env->lenb) \
			? "rb" : "rrb");
	if (env->b)
		printlist(env);
	while (env->b)
		execute(env, "pa");
	env->to_push = NULL;
	printlist(env);
}

void	push_2b(t_ps *env)
{
	t_card				*f;
	t_card				*l;
	unsigned long int	c;

	env->to_push = env->a;
	env->to_push->cplex = env->lena + env->lenb;
	f = env->a;
	l = env->alast;
	c = 0;
	while (f && l && c <= (env->lena + env->lenb) / 2)
	{
		f->cplex = get_cplex(env, f, c);
		l->cplex = get_cplex(env, l, env->lena - 1 - c++);
		if ((f == env->to_push && f->cplex <= c - 1) \
			|| (l == env->to_push && l->cplex <= c))
			break ;
		f = f->next;
		l = l->prev;
	}
	organize(env, env->to_push->cplex, env->abcd);
	env->error = env->a->value;
	if (env->to_push->value == env->mina && (f = env->a))
		while ((f = f->next))
			env->error = (env->error > f->value) ? f->value : env->error;
	env->mina = (env->to_push->value == env->mina) ? c : env->mina;
}

int		push_swap(t_ps *env)
{
	if (env->lena < 3 && env->lena > 1 && env->a->value > env->a->next->value)
		execute(env, "sa");
	if (env->lena == 3 \
		|| (is_asce_sorted(env->a) && (!env->b || env->mina > env->maxb)))
	{
		printlist(env);
		end_sort(env);
	}
	else if (env->lena > 3)
	{
		push_2b(env);
		return (push_swap(env));
	}
	while (env->a)
	{
		env->to_push = (env->a)->next;
		ft_bzero(env->a, sizeof(*env->a));
		ft_memdel((void **)&env->a);
		env->a = env->to_push;
	}
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	t_ps			env;
	int				*tab;
	unsigned int	i;

	if (ac < 2 || !boot(ac, av, &env))
		return (0);
	if (!env.lena || !(tab = (int *)malloc(sizeof(int) * env.lena)))
		leave(&env.a, &env.b, "\n");
	env.to_push = env.a;
	i = 0;
	while (i < env.lena)
	{
		tab[i] = env.to_push->value;
		env.to_push = env.to_push->next;
		i = i + 1;
	}
	ft_ascendingsort(tab, env.lena);
	env.mina = tab[0];
	env.maxa = (env.lena > 3) ? tab[env.lena - 3] : tab[env.lena - 1];
	env.minb = env.maxa;
	env.maxb = env.mina;
	ft_memdel((void **)&tab);
	return (push_swap(&env));
}
