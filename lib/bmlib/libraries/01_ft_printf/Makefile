# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 13:15:04 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/10/10 04:50:23 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libftprintf.a

#NAME =		ft_printf.out

SRCS =		ft_printf/a_ft_printf.c				ft_printf/ft_putchar.c		\
			ft_printf/b_ft_read.c				ft_printf/ft_putstr.c		\
			ft_printf/ft_itoa.c					ft_printf/ft_strlen.c		\
			ft_printf/ft_ptoa.c					ft_printf/ft_uitoa.c		\
			ft_printf/ft_10to16.c

 BNS_SRCS =	ft_printf_bonus/a_ft_printf_bonus.c	ft_printf_bonus/ft_putchar_bonus.c		\
			ft_printf_bonus/b_ft_read_bonus.c	ft_printf_bonus/ft_putstr_bonus.c		\
			ft_printf_bonus/ft_itoa_bonus.c		ft_printf_bonus/ft_a_convert_i_bonus.c	\
			ft_printf_bonus/ft_ptoa_bonus.c		ft_printf_bonus/ft_uitoa_bonus.c		\
			ft_printf_bonus/ft_10to16_bonus.c

OBJS =		$(SRCS:.c=.o)

BNS_OBJS =	$(BNS_SRCS:.c=.o)

FLAGS =		-Werror -Wextra -Wall
#FLAGS =		-g 

CC = 		gcc

LIBR = 		ft_printf/ft_printf.h

LIBR_BNS =	ft_printf_bonus/ft_printf_bonus.h

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all:		$(NAME)

%.o: %.c $(LIBR)
	@echo "$(BLUE) compiling $<"
	@echo "$(GRAY)"
	$(CC) $(FLAGS) -c $< -o $@
	@echo "$(CYAN)--------------------------------------------------------------"

$(NAME):	$(OBJS) $(LIBR)
			@echo "$(YELLOW)\n\nlinking...$(GRAY)"
			@ar -rcs $(NAME) $(OBJS)
			@echo "$(GREEN)\n🌐 LIBRARY FOR FT_PRINTF WITHOUT BONUS COMPILED 🌐$(DEF_COLOR)\n"

bonus:		$(BNS_OBJS) $(LIBR_BNS)
			@echo "$(YELLOW)\n\nlinking...$(GRAY)"
			@ar -rcs $(NAME) $(BNS_OBJS)
			@echo "$(GREEN)\n🌐 LIBRARY FOR FT_PRINTF WITH BONUS COMPILED 🌐$(DEF_COLOR)\n"

#bonus:		$(BNS_OBJS) $(LIBR)
#			$(CC) $(FLAGS) $(BNS_OBJS) -o $(NAME)

clean:
			@rm -f	$(OBJS)
			@rm -f 	$(BNS_OBJS)

fclean:		clean
			@rm -f	$(NAME)

re:			fclean all

.PHONY: all clean fclean re
