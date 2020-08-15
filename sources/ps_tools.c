/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:55:22 by yaye              #+#    #+#             */
/*   Updated: 2020/01/20 14:55:23 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "push_swap.h"

void	execute(t_ps *env, char *operation)
{
	operate(env, operation);
	write(1, operation, ft_strlen(operation));
	write(1, "\n", 1);
}

int		get_c(t_ps *env, t_card *p)
{
	t_card	*tmp;
	int		c;

	c = 0;
	if (!(tmp = env->b))
		return (0);
	if (p->value >= env->maxb || p->value <= env->minb)
		while (tmp && tmp->value != env->maxb && ++c)
			tmp = tmp->next;
	else
	{
		while (tmp && tmp->value <= p->value && ++c)
			tmp = tmp->next;
		while (tmp && tmp->value > p->value && ++c)
			tmp = tmp->next;
	}
	return (c);
}

int		get_cplex(t_ps *env, t_card *p, int pos)
{
	t_card				*tmp;
	unsigned int		t[5];
	int					i;

	if (p->value >= env->maxa)
		return (env->lena + env->lenb);
	tmp = env->a;
	t[0] = pos;
	t[1] = env->lena - t[0];
	t[2] = get_c(env, p);
	t[3] = env->lenb - t[2];
	t[4] = ft_min(ft_min(t[0], t[2]) + ft_abs(t[0] - t[2]), t[0] + t[3]);
	t[4] = ft_min(ft_min(t[1], t[3]) + ft_abs(t[1] - t[3]), t[4]);
	t[4] = ft_min(t[4], t[1] + t[2]);
	i = -1;
	if (t[4] < env->to_push->cplex && (env->to_push = p))
		while (++i < 4)
			env->abcd[i] = t[i];
	return (t[4]);
}

int		organize0(t_ps *env, int cplex, int *t)
{
	int		i;

	if (cplex == ft_min(t[0], t[2]) + ft_abs(t[0] - t[2]))
	{
		i = ft_min(t[0], t[2]);
		while (--i >= 0)
			execute(env, "rr");
		i = ft_abs(t[0] - t[2]);
		while (--i >= 0)
			execute(env, (t[0] > t[2]) ? "ra" : "rb");
		return (1);
	}
	else if (cplex == ft_min(t[1], t[3]) + ft_abs(t[1] - t[3]))
	{
		i = ft_min(t[1], t[3]);
		while (--i >= 0)
			execute(env, "rrr");
		i = ft_abs(t[1] - t[3]);
		while (--i >= 0)
			execute(env, (t[1] > t[3]) ? "rra" : "rrb");
		return (1);
	}
	return (0);
}

void	organize(t_ps *env, int cplex, int *t)
{
	printlist(env);
	if (organize0(env, cplex, t))
		;
	else if (cplex == t[0] + t[3])
	{
		while (--t[0] >= 0)
			execute(env, "ra");
		while (--t[3] >= 0)
			execute(env, "rrb");
	}
	else if (cplex == t[1] + t[2])
	{
		while (--t[1] >= 0)
			execute(env, "rra");
		while (--t[2] >= 0)
			execute(env, "rb");
	}
	if (env->maxb < env->to_push->value)
		env->maxb = env->to_push->value;
	if (env->minb > env->to_push->value)
		env->minb = env->to_push->value;
	execute(env, "pb");
}
