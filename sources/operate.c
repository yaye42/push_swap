/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 18:34:12 by yaye              #+#    #+#             */
/*   Updated: 2019/12/03 18:34:13 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_ps *env, t_card **card)
{
	t_card	*p;

	env->error = 0;
	if (!(*card) || !(*card)->next)
		return ;
	p = (*card);
	(*card) = (*card)->next;
	p->next = (*card)->next;
	(*card)->next = p;
	(*card)->prev = NULL;
	p->prev = (*card);
	if (p->next)
		p->next->prev = p;
}

void	push(t_ps *env, t_card **tosser, t_card **receiver)
{
	t_card	*p;

	env->error = 0;
	if (!(*tosser))
		return ;
	p = *receiver;
	*receiver = *tosser;
	*tosser = (*tosser)->next;
	(*receiver)->next = p;
	if (p)
		p->prev = *receiver;
	if (*receiver == env->a)
		env->alast = (p) ? env->alast : env->a;
	if (*receiver == env->b)
		env->blast = (p) ? env->blast : env->b;
	if (*tosser)
		(*tosser)->prev = NULL;
	if (*tosser == env->b)
		env->blast = (env->b) ? env->blast : NULL;
	if (*tosser == env->a)
		env->alast = (env->a) ? env->alast : NULL;
}

void	rot(t_ps *env, t_card **first, t_card **last)
{
	t_card	*p;

	env->error = 0;
	if (!(*first) || !(*first)->next)
		return ;
	p = *first;
	*first = (*first)->next;
	(*last)->next = p;
	p->prev = *last;
	p->next = NULL;
	(*first)->prev = NULL;
	*last = p;
}

void	rev_rot(t_ps *env, t_card **first, t_card **last)
{
	t_card	*p;

	env->error = 0;
	if (!(*first) || !(*first)->next)
		return ;
	p = (*last)->prev;
	(*last)->next = *first;
	(*first)->prev = *last;
	(*last)->prev = NULL;
	p->next = NULL;
	*first = *last;
	*last = p;
}

void	operate(t_ps *env, char *buf)
{
	if (ft_strequ(buf, "sa") || ft_strequ(buf, "ss"))
		swap(env, &env->a);
	if (ft_strequ(buf, "sb") || ft_strequ(buf, "ss"))
		swap(env, &env->b);
	if (ft_strequ(buf, "pa"))
	{
		push(env, &env->b, &env->a);
		env->lena++;
		env->lenb--;
	}
	if (ft_strequ(buf, "pb"))
	{
		push(env, &env->a, &env->b);
		env->lena--;
		env->lenb++;
	}
	if (ft_strequ(buf, "ra") || ft_strequ(buf, "rr"))
		rot(env, &env->a, &env->alast);
	if (ft_strequ(buf, "rb") || ft_strequ(buf, "rr"))
		rot(env, &env->b, &env->blast);
	if (ft_strequ(buf, "rra") || ft_strequ(buf, "rrr"))
		rev_rot(env, &env->a, &env->alast);
	if (ft_strequ(buf, "rrb") || ft_strequ(buf, "rrr"))
		rev_rot(env, &env->b, &env->blast);
}
