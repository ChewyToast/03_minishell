# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42bcn>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 04:26:35 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/10/10 04:26:39 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		gnl.a

SRCS =		src/get_next_line.c		src/get_next_line_utils.c

BNS_SRCS =	src/get_next_line_utils_bonus.c		src/get_next_line_bonus.c

OBJS =		$(SRCS:.c=.o)

BNS_OBJS =	$(BNS_SRCS:.c=.o)

FLAGS =		-Werror -Wextra -Wall

CC = 		gcc

LIBR = 		src/get_next_line.h

LIBR_BNS =	src/get_next_line_bonus.h

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
			@echo "$(GREEN)\n🌐 LIBRARY FOR gnl WITHOUT BONUS COMPILED 🌐$(DEF_COLOR)\n"

bonus:		$(BNS_OBJS) $(LIBR_BNS)
			@echo "$(YELLOW)\n\nlinking...$(GRAY)"
			@ar -rcs $(NAME) $(BNS_OBJS)
			@echo "$(GREEN)\n🌐 LIBRARY FOR gnl WITH BONUS COMPILED 🌐$(DEF_COLOR)\n"


clean:
			@rm -f	$(OBJS)
			@rm -f 	$(BNS_OBJS)

fclean:		clean
			@rm -f	$(NAME)

re:			fclean all

.PHONY: all clean fclean re
