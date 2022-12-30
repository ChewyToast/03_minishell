# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: test <test@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 22:17:08 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/12/30 13:33:50 by test             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

FILES =	minishell.c				\
		parsing/parser.c		\
		parsing/utils.c			\
		parsing/env.c			\
		parsing/env_utils.c		\
		parsing/tokenizer.c		\
		executor/executor.c 	\
    	executor/exec_utils.c 	\
		executor/path.c

SDIR = src

TDIR = .obj

SRC =	$(addprefix $(SDIR)/, $(FILES))

OBJS =	$(addprefix $(TDIR)/, $(notdir $(FILES:.c=.o)))

DEPS =	$(addprefix $(TDIR)/, $(notdir $(FILES:.c=.d)))

GCC =	gcc

RM =	rm -rf

MKF =	Makefile

FLAGS =	-Werror -Wextra -Wall -g -MMD 

#-fsanitize=address

INCL =	-I inc/headers -I inc/libs

LIBS =	inc/libs

LIB_A =	inc/libs/bmlib.a

GSU =	git submodule update

GSU_FLAGS =	--remote --merge --recursive

all:
		@$(MAKE) -C $(LIBS)
		@$(MAKE) $(NAME)

clean:
		@$(MAKE) clean -C $(LIBS)
		$(RM) $(OBJS) $(DEPS)

fclean:
		@$(MAKE) fclean -C $(LIBS)
		$(RM) $(OBJS) $(DEPS) $(NAME)

update:
		$(GSU) $(GSU_FLAGS)

re:
		@$(MAKE) fclean
		@$(MAKE) all

$(NAME):$(TDIR) $(OBJS)
		$(GCC) $(FLAGS) -lreadline $(OBJS) $(LIB_A) -o $(NAME)

$(TDIR):
		@mkdir -p -m700 $@

$(TDIR)/%.o:$(SDIR)/%.c $(LIB_A) $(MKF)
			@$(GCC) $(FLAGS) $(INCL) -c $< -o $(TDIR)/$(notdir $@)
			@echo "compiled minishell file: <$(notdir $<)>"

$(TDIR)/%.o:$(SDIR)/parsing/%.c $(LIB_A) $(MKF)
			@$(GCC) $(FLAGS) $(INCL) -c $< -o $(TDIR)/$(notdir $@)
			@echo "compiled minishell file: <$(notdir $<)>"
			
$(TDIR)/%.o:$(SDIR)/executor/%.c $(LIB_A) $(MKF)
			@$(GCC) $(FLAGS) $(INCL) -c $< -o $(TDIR)/$(notdir $@)
			@echo "compiled minishell file: <$(notdir $<)>"			

-include $(DEPS)

.PHONY:	all bonus update clean fclean re