/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:55:07 by yaye              #+#    #+#             */
/*   Updated: 2019/04/09 19:26:54 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdarg.h>
# define BUFF_SIZE 8
# define PF_BUF 5000

/*
** >---------------------- LINKED LIST MANIPULATION --------------------------<
*/

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstlst(t_list *lst_start, void *needle);
t_list				*ft_lstlast(t_list *lst_start);
t_list				*ft_strsplit_lst(char const *s, char c);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstaddbel(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** >------------------------- STRING MANIPULATION ----------------------------<
*/

size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, \
	const char *needle, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					get_next_line(const int fd, char **line);

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				*ft_memdel(void **ap);

/*
** >------------------------- PRINTING FUNCTIONS -----------------------------<
*/

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_printbits(unsigned char c);

/*
** >------------------------------ FT_PRINTF ---------------------------------<
*/

typedef struct		s_pf
{
	va_list			vali;
	char			str[PF_BUF];
	int				i;
	int				len;
}					t_pf;

typedef struct		s_flg
{
	int				hsh;
	int				spc;
	int				pls;
	int				zro;
	int				neg;
}					t_flg;

typedef	struct		s_arg
{
	t_flg			flg;
	int				fld;
	int				prc;
	int				mod;
	int				typ;
	int				len;
	int				fill;
	int				extra;
	int				i;
	char			*p;
	char			f[81];
	char			inf[81];
	char			nan[81];
}					t_arg;

int					ft_printf(const char *str, ...);
void				fill_buf(t_pf *env, char c);
void				new_arg(t_arg *new);
void				to_u(unsigned long u, char *s, t_arg *arg);
void				to_bi(long double f, char *s);
int					parse(const char *str, t_pf *env);
void				parse_di(t_pf *env, t_arg *arg);
void				parse_o(t_pf *env, t_arg *arg);
void				parse_u(t_pf *env, t_arg *arg);
void				parse_x(t_pf *env, t_arg *arg);
void				parse_xcap(t_pf *env, t_arg *arg);
void				parse_c(t_pf *env, t_arg *arg);
void				parse_s(t_pf *env, t_arg *arg);
void				parse_p(t_pf *env, t_arg *arg);
void				parse_f(t_pf *env, t_arg *arg);
void				parse_percent(t_pf *env, t_arg *arg);
void				parse_b(t_pf *env, t_arg *arg);
int					naninf(long double n, char *s, t_arg *arg);

/*
** >------------------------------ QUICK MATH --------------------------------<
*/

unsigned long		ft_power(int x, int power);
int					ft_abs(int x);
int					ft_min(int a, int b);
int					ft_max(int a, int b);
int					ft_log2(int x);
int					ft_hexatod(char *str);
int					ft_atoi_base(char *str, char *base);
void				ft_ascendingsort(int *tab, int len);

/*
** >-------------------------------- OTHERS ----------------------------------<
*/

char				*ft_itoa(int n);
int					ft_atoi(const char *str);
int					ft_stoi(char *str, int *i, char c);
unsigned int		ft_igap(int a, int b);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isblanc(int c);
#endif
