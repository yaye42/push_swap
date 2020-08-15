/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:20:20 by yaye              #+#    #+#             */
/*   Updated: 2020/01/21 15:20:21 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "push_swap.h"

void	printlist(t_ps *env)
{
	t_card	*l;
	t_card	*m;

	if (!env->v)
		return ;
	l = env->a;
	m = env->b;
	ft_printf("\n%11s   	%11s\n", "A", "B", 2);
	while (l || m)
	{
		if (l)
			ft_printf("%11d", l->value, 2);
		else
			write(2, "           ", 11);
		write(2, (l == env->to_push && env->to_push) ? " <-	" : "   	", 4);
		if (m)
			ft_printf("%11d", m->value, 2);
		l = (l) ? l->next : NULL;
		m = (m) ? m->next : NULL;
		write(2, "\n", 1);
	}
}

int		ft_stou(char *str, unsigned long int *u, char c)
{
	int					j;
	unsigned long int	n;

	j = 0;
	if (str[j] != '+' && !ft_isdigit(str[j]))
		return (0);
	if (!(n = 0) && !ft_isdigit(str[j]) && !ft_isdigit(str[++j]))
		return (0);
	while (ft_isdigit(str[j]))
		if (n > 429496729 || (n = n * 10 + str[j++] - '0') > 4294967296)
			return (0);
	if (str[j] && str[j] != c)
		return (0);
	*u = n;
	return (j);
}

int		get_r(int ac, char **av, t_ps *env, int *j)
{
	int					min;
	int					max;
	unsigned long int	n;
	int					x;

	if (*j + 2 >= ac)
		leave(&env->a, &env->b, "\nusage: ./push_swap -r [MIN] [MAX] [n]\n");
	if (!ft_stoi(av[(*j)++], &min, '\0') || !ft_stoi(av[(*j)++], &max, '\0') \
		|| !ft_stou(av[(*j)++], &n, '\0') || min < -65536 || max > 65536 \
		|| n > ft_igap(min, max) || !n)
		return (0);
	if (min >= max)
		leave(&env->a, &env->b, ": [MIN] >= [MAX]\n");
	srand(time(0));
	while (n > 0)
	{
		x = rand() % (max - min) + min;
		while (!unique(env, x))
			x = rand() % (max - min) + min;
		n = n - 1;
	}
	return (1);
}

void	bonus_parsing(t_ps *env, char *av)
{
	int		j;

	if (env->r)
		leave(&env->a, &env->b, "\nusage: ./push_swap -r [MIN] [MAX] [n]\n");
	j = 0;
	while (av[++j])
	{
		env->r = (av[j] == 'r') ? 1 : env->r;
		env->v = (av[j] == 'v') ? 1 : env->v;
		env->h = (av[j] == 'h') ? 1 : env->h;
		env->error = (av[j] == 'o') ? 1 : env->error;
		if (av[j] != 'r' && av[j] != 'v' && av[j] != 'h' && av[j] != 'o')
			leave(&env->a, &env->b, ": ./push_swap -h for help.\n");
	}
	if (env->h)
	{
		write(1, "\nThe following options are available:\n\n-r [MIN] [MAX] [n]\
\n   Generate [n] random values between [MIN] and [MAX] as parameters.\n|Value\
s| <= 65536\n\n-v\n   Display the stacks' status.\n\n-o\n   Use arguments in .\
/ARGUMENTS\n\n", 217);
		exit(0);
	}
}

int		bonus(int ac, char **av, t_ps *env)
{
	int		i;
	int		fd;
	int		gnl;
	char	*line;

	i = 0;
	while (++i < ac && av[i][0] == '-' && (av[i][1] == 'v' \
		|| av[i][1] == 'r' || av[i][1] == 'h' || av[i][1] == 'o'))
		bonus_parsing(env, av[i]);
	if (env->r && env->error)
		leave(&env->a, &env->b, ": option -r and -o not compatible\n");
	if (env->r && !get_r(ac, av, env, &i))
		leave(&env->a, &env->b, "\n-r: |Values| <= 65536 & MAX - MIN >= n.\n");
	if (env->error)
	{
		if ((fd = open("ARGUMENTS", O_RDONLY)) <= 2)
			leave(&env->a, &env->b, ": failed to open ./ARGUMENTS.\n");
		while ((gnl = get_next_line(fd, &line)) > 0)
			if (!parsing(env, line) && !ft_memdel((void **)&line))
				leave(&env->a, &env->b, ": unvalid passed argument.\n");
		if (!ft_memdel((void **)&line) && gnl == -1)
			leave(&env->a, &env->b, ": failed to read in ./ARGUMENTS.\n");
		close(fd);
	}
	return (i);
}
