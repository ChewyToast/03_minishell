# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 22:17:08 by bmoll-pe          #+#    #+#              #
#    Updated: 2023/01/11 20:21:33 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

FILES =	minishell.c\
		parsing/parser.c\
		parsing/tokenizer.c\
		parsing/env.c\
		executor/executor.c\
		executor/path.c\
		executor/wildcard.c\
    	utils/exec_utils.c\
		utils/wildcard_utils.c\
		utils/utils.c\
		utils/env_utils.c\
		utils/path_utils.c\
		utils/mem_utils.c

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

-include $(DEPS)

.PHONY:	all bonus update clean fclean re