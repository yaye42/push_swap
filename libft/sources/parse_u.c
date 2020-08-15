/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 11:46:27 by yaye              #+#    #+#             */
/*   Updated: 2019/07/25 11:46:29 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	to_u(unsigned long u, char *s, t_arg *arg)
{
	if (u < 10)
	{
		arg->len++;
		s[arg->i++] = u + '0';
	}
	else
	{
		arg->len++;
		to_u(u / 10, s, arg);
		s[arg->i++] = u % 10 + '0';
	}
}

void	fill_uneg(char *n, t_pf *env, t_arg *arg)
{
	int		i;

	if (arg->prc == 0 && n[0] == '0')
		arg->len = 0;
	arg->prc = (arg->prc < arg->len) ? 0 : arg->prc - arg->len;
	if (arg->extra)
	{
		fill_buf(env, arg->extra);
		arg->fill = arg->fld - (arg->prc++ + arg->len);
	}
	else
		arg->fill = arg->fld - (arg->prc++ + arg->len) + 1;
	while (--arg->prc > 0)
		fill_buf(env, '0');
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
	while (--arg->fill > 0)
		fill_buf(env, ' ');
}

void	fill_uzro(char *n, t_pf *env, t_arg *arg)
{
	int		i;

	if (arg->extra)
	{
		fill_buf(env, arg->extra);
		arg->fill = arg->fld - arg->len;
	}
	else
		arg->fill = arg->fld - arg->len + 1;
	while (--arg->fill > 0)
		fill_buf(env, '0');
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
}

void	fill_uels(char *n, t_pf *env, t_arg *arg)
{
	int		i;

	if (arg->prc == 0 && n[0] == '0')
		arg->len = 0;
	arg->prc = (arg->prc < arg->len) ? 0 : arg->prc - arg->len;
	arg->fill = (arg->extra) ? arg->fld - (arg->prc++ + arg->len) \
		: arg->fld - (arg->prc++ + arg->len) + 1;
	while (--arg->fill > 0)
		fill_buf(env, ' ');
	if (arg->extra)
		fill_buf(env, arg->extra);
	while (--arg->prc > 0)
		fill_buf(env, '0');
	i = -1;
	while (++i < arg->len)
		fill_buf(env, n[i]);
}

void	parse_u(t_pf *env, t_arg *arg)
{
	unsigned long	d;
	char			n[21];

	arg->extra = (arg->flg.pls) ? arg->flg.pls : arg->flg.spc;
	if (arg->prc >= 0)
		arg->flg.zro = 0;
	if (arg->mod >= 3)
		d = (unsigned long)va_arg(env->vali, intmax_t);
	else if (arg->mod == 2)
		d = (unsigned short)va_arg(env->vali, intmax_t);
	else if (arg->mod == 1)
		d = (unsigned char)va_arg(env->vali, intmax_t);
	else
		d = va_arg(env->vali, unsigned int);
	ft_bzero(n, 21);
	to_u(d, n, arg);
	if (arg->flg.neg)
		fill_uneg(n, env, arg);
	else if (arg->flg.zro)
		fill_uzro(n, env, arg);
	else
		fill_uels(n, env, arg);
}
