# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 22:17:08 by bmoll-pe          #+#    #+#              #
#    Updated: 2023/01/28 23:37:07 by aitoraudica      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

FILES =	minishell.c\
		parsing/check_cmd.c\
		parsing/env.c\
		parsing/parser.c\
		parsing/syntax_check.c\
		parsing/tokenizer.c\
		parsing/redirects.c\
		buildin/envoirment.c\
		buildin/directories.c\
		buildin/exit.c\
		buildin/echo.c\
		executor/executor.c\
		executor/wildcard.c\
		executor/exec_cmd.c\
		utils/buildin_utils.c\
		executor/expander.c\
		utils/env_utils.c\
    	utils/exec_utils.c\
		utils/mem_utils.c\
		utils/parser_utils.c\
		utils/path_utils.c\
		utils/utils.c\
		utils/wildcard_utils.c

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
		$(RM) $(TDIR)

fclean:
		@$(MAKE) fclean -C $(LIBS)
		$(RM) $(TDIR) $(NAME)

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

$(TDIR)/%.o:$(SDIR)/utils/%.c $(LIB_A) $(MKF)
		@$(GCC) $(FLAGS) $(INCL) -c $< -o $(TDIR)/$(notdir $@)
		@echo "compiled minishell file: <$(notdir $<)>"

$(TDIR)/%.o:$(SDIR)/buildin/%.c $(LIB_A) $(MKF)
		@$(GCC) $(FLAGS) $(INCL) -c $< -o $(TDIR)/$(notdir $@)
		@echo "compiled minishell file: <$(notdir $<)>"

-include $(DEPS)

.PHONY:	all bonus update clean fclean re