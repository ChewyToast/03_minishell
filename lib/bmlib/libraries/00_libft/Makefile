# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42bcn>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 04:23:57 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/11/29 18:03:13 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =		ft_atoi.c		ft_memmove.c	ft_strlcpy.c	\
			ft_bzero.c		ft_memset.c		ft_strlen.c		\
			ft_calloc.c		ft_putchar_fd.c	ft_strmapi.c	\
			ft_isalnum.c	ft_putendl_fd.c	ft_strncmp.c	\
			ft_isalpha.c	ft_putnbr_fd.c	ft_strnstr.c	\
			ft_isascii.c	ft_putstr_fd.c	ft_strrchr.c	\
			ft_isdigit.c	ft_split.c		ft_strrspn.c	\
			ft_isprint.c	ft_strchr.c		ft_strspn.c		\
			ft_itoa.c		ft_strdup.c		ft_strtrim.c	\
			ft_memchr.c		ft_striteri.c	ft_substr.c		\
			ft_memcmp.c		ft_strjoin.c	ft_tolower.c	\
			ft_memcpy.c		ft_strlcat.c	ft_toupper.c	\
			ft_isspace.c

BNS_SRCS =	ft_lstnew_bonus.c		ft_lstadd_front_bonus.c		\
			ft_lstsize_bonus.c		ft_lstlast_bonus.c			\
			ft_lstadd_back_bonus.c	ft_lstdelone_bonus.c		\
			ft_lstclear_bonus.c		ft_lstiter_bonus.c			\
			ft_lstmap_bonus.c

OBJS =		$(SRCS:.c=.o)

BNS_OBJS =	$(BNS_SRCS:.c=.o)

FLAGS =		-Werror -Wextra -Wall -c

CC = 		gcc

LIBR = 		libft.h

all:		$(NAME)

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
			@echo "$(GREEN)\n🌐 LIBRARY LIBFT WITHOUT BONUS COMPILED 🌐$(DEF_COLOR)\n"

bonus:		$(OBJ) $(BNS_OBJS) $(LIBR)
			@echo "$(YELLOW)\n\nlinking...$(GRAY)"
			@ar -rcs $(NAME) $(OBJ) $(BNS_OBJS)
			@echo "$(GREEN)\n🌐 LIBRARY LIBFT WITH BONUS COMPILED 🌐$(DEF_COLOR)\n"

clean:
			@rm -f	$(OBJS)
			@rm -f	$(BNS_OBJS)

fclean:		clean
			@rm -f	$(NAME)
			@rm -f	bonus

re:			fclean all

.PHONY: all clean fclean re
