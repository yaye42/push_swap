/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:40:29 by yaye              #+#    #+#             */
/*   Updated: 2019/12/03 13:40:30 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"

/*
** >-------------------------- PUSH_SWAP STRUCTURES --------------------------<
*/

typedef struct		s_card
{
	int				value;
	unsigned int	cplex;
	struct s_card	*prev;
	struct s_card	*next;
}					t_card;

typedef struct		s_ps
{
	t_card			*a;
	t_card			*alast;
	t_card			*b;
	t_card			*blast;
	t_card			*to_push;
	char			*l;
	unsigned int	lena;
	unsigned int	lenb;
	int				mina;
	int				maxa;
	int				minb;
	int				maxb;
	int				error;
	int				r;
	int				v;
	int				h;
	int				abcd[4];
}					t_ps;

/*
** >-------------------------------- FUNCTIONS -------------------------------<
*/

void				leave(t_card **carda, t_card **cardb, char *msg);
void				operate(t_ps *env, char *buf);
void				execute(t_ps *env, char *operation);
int					is_asce_sorted(t_card *card);
int					get_cplex(t_ps *env, t_card *p, int pos);
void				organize(t_ps *env, int cplex, int *t);
int					unique(t_ps *env, int x);
int					parsing(t_ps *env, char *str);
int					boot(int ac, char **av, t_ps *env);
void				printlist(t_ps *env);
int					bonus(int ac, char **av, t_ps *env);
#endif
