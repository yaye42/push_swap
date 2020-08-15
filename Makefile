# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaye <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 11:17:35 by yaye              #+#    #+#              #
#    Updated: 2020/02/26 16:14:49 by yaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHCK = checker
PUSW = push_swap
CC	 = clang
CFLAGS = -Wall -Wextra -Werror -Wpadded
#CFLAGS += -fsanitize=address,undefined -g3
INCL = -Iincludes -Ilibft/includes

LBFT = libft/libft.a

CC_S = checker.c
PS_S = push_swap.c ps_tools.c
CM_S = operate.c tools.c bonus.c

ODIR = ./objects/
CC_O = $(patsubst %.c, $(ODIR)%.o, $(CC_S))
PS_O = $(patsubst %.c, $(ODIR)%.o, $(PS_S))
CM_O = $(patsubst %.c, $(ODIR)%.o, $(CM_S))

HEAD = includes/push_swap.h

ARG = ARGUMENTS

vpath %.c ./sources/

all : $(ODIR) $(CHCK) $(PUSW)

$(CHCK) : $(LBFT) $(CM_O) $(CC_O)
	$(CC) $(CFLAGS) -o $@ $(CC_O) $(CM_O) $(INCL) -Llibft/ -lft
	@printf "\033[1;32m%35s	COMPILED\033[0m\n" "$(CHCK)"

$(PUSW) : $(LBFT) $(CM_O) $(PS_O)
	$(CC) $(CFLAGS) -o $@ $(PS_O) $(CM_O) $(INCL) -Llibft/ -lft
	@printf "\033[1;32m%35s	COMPILED\033[0m\n" "$(PUSW)"

$(LBFT) : FORCE
	@$(MAKE) -C libft

$(CM_O) : $(ODIR)%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@printf "\033[32m%35s	COMPILED\033[0m\n" "$@"

$(CC_O) : $(ODIR)%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@printf "\033[32m%35s	COMPILED\033[0m\n" "$@"

$(PS_O) : $(ODIR)%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@printf "\033[32m%35s	COMPILED\033[0m\n" "$@"

$(ODIR) :
	@mkdir $@

FORCE :

clean :
	$(RM) $(CM_O)
	$(RM) $(CC_O)
	$(RM) $(PS_O)
	$(RM) $(ARG)
	$(RM) -R $(ODIR)
	$(MAKE) clean -C libft

fclean : clean
	$(RM) $(CHCK)
	@printf "\033[31m%35s	REMOVED\033[0m\n" "$(CHCK)"
	$(RM) $(PUSW)
	@printf "\033[31m%35s	REMOVED\033[0m\n" "$(PUSW)"
	$(RM) $(LBFT)
	@printf "\033[31m%35s	REMOVED\033[0m\n" "$(LBFT)"

re : fclean
	@$(MAKE)

#.SILENT:
.PHONY: all FORCE clean fclean re
