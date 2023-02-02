# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 22:17:08 by bmoll-pe          #+#    #+#              #
#    Updated: 2023/02/02 01:59:21 by ailopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# Project Variables
################################################################################

NAME =	minishell

################################################################################
# Compiler & Flags
################################################################################

# Compiler
GCC := gcc

# Compiler flags
FLAGS :=	-Werror -Wextra -Wall -g -MMD

# Remove
RM 	:=	rm -rf

# Makefile
MKF :=	Makefile

# Git
GSU =	git submodule update
GSU_FLAGS =	--remote --merge --recursive

# Address sanitizing flags
ASAN := -fsanitize=address -fsanitize-recover=address
ASAN += -fno-omit-frame-pointer -fno-common
ASAN += -fsanitize=pointer-subtract -fsanitize=pointer-compare
# Technicaly UBSan but works with ASan
ASAN += -fsanitize=undefined
# Technicaly LSan but works with ASan
# ASAN += -fsanitize=leak
# Thread sanitizing flags
TSAN := -fsanitize=thread
# Memory sanitizing flags
MSAN := -fsanitize=memory -fsanitize-memory-track-origins

################################################################################
# Root Folders
################################################################################

SRC_ROOT := src/
DEP_ROOT := .dep/
OBJ_ROOT := .obj/
INC_ROOT := inc/
LIB_ROOT := ${INC_ROOT}libs/

################################################################################
# Content Folders
################################################################################

# List of folders with header files.Each folder needs to end with a '/'. The
# path to the folders is relative to the root of the makefile. Library includes
# can be specified here.

INC_DIRS += ${INC_ROOT}

################################################################################
# Libraries
################################################################################

# bmlib
BMLIB_ROOT := ${LIB_ROOT}
BMLIB_INC := ${BMLIB_ROOT}
BMLIB := ${BMLIB_ROOT}bmlib.a

INC_DIRS += ${BMLIB_INC}
LIBS += -L${BMLIB_INC}

# Lib readline
READLINE_ROOT := ${LIB_ROOT}libraries/readline/
READLINE := ${READLINE_ROOT}libreadline.a ${READLINE_ROOT}libhistory.a

INC_DIRS += ${READLINE_ROOT}
LIBS += -L${READLINE_ROOT} -lreadline -lhistory -ltermcap

################################################################################
# Files
################################################################################

FILES =	minishell.c					parsing/check_cmd.c\
		parsing/env.c				parsing/parser.c\
		parsing/syntax_check.c		parsing/tokenizer.c\
		parsing/redirects.c			buildin/envoirment.c\
		buildin/directories.c		buildin/exit.c\
		buildin/echo.c				executor/executor.c\
		executor/wildcard.c			executor/exec_cmd.c\
		utils/buildin_utils.c		executor/expander.c\
		utils/env_utils.c			utils/exec_utils.c\
		utils/mem_utils.c			utils/parser_utils.c\
		utils/path_utils.c			utils/utils.c\
		utils/wildcard_utils.c

SRC 	:= $(addprefix $(SRC_ROOT), $(FILES))
OBJS 	:= $(addprefix $(OBJ_ROOT), $(notdir $(FILES:.c=.o)))
DEPS 	:= $(addprefix $(DEP_ROOT), $(notdir $(FILES:.c=.d)))
INCS 	:= -I $(INC_ROOT)/headers -I $(INC_ROOT)/libs -I $(READLINE_ROOT)

################################################################################
# Colort
################################################################################

DEL_LINE =		\033[2K
ITALIC =		\033[3m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
DARK_YELLOW =	\033[38;5;143m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
DARK_GREEN =	\033[1m\033[38;2;75;179;82m

################################################################################
# Project Target
################################################################################

all:
		@$(MAKE) -C $(BMLIB_ROOT)
		@$(MAKE) -sC $(READLINE_ROOT)
		@echo "$(DARK_GREEN)GNU readline 8.2 COMPILED ✅$(DEF_COLOR)"
		@$(MAKE) $(NAME)

clean:
		@$(MAKE) clean -C $(BMLIB_ROOT)
		@$(MAKE) clean -C $(READLINE_ROOT)
		$(RM) $(OBJS)

fclean:
		@$(MAKE) fclean -C $(BMLIB_ROOT)
		$(RM) $(NAME)

update:
		$(GSU) $(GSU_FLAGS)

re:
		@$(MAKE) fclean
		@$(MAKE) all

$(NAME):$(OBJ_ROOT) $(OBJS)
		@$(GCC) $(FLAGS) $(OBJS) $(READLINE) $(BMLIB) $(LIBS) -o $(NAME)
		@echo "$(DARK_GREEN)⚡ MINISHELL COMPILED ✅$(DEF_COLOR)"

$(OBJ_ROOT):
		@mkdir -p -m700 $@
$(DEP_ROOT):
		@mkdir -p -m700 $@

$(OBJ_ROOT)%.o:$(SRC_ROOT)%.c $(READLINE) $(BMLIB) $(MKF)
		@$(GCC) $(FLAGS) $(INCS) -c $< -o $(OBJ_ROOT)$(notdir $@)
		@echo "▶ Compiled minishell file: <$(notdir $<)>"

$(OBJ_ROOT)%.o:$(SRC_ROOT)parsing/%.c $(BMLIB) $(MKF)
		@$(GCC) $(FLAGS) $(INCS) -c $< -o $(OBJ_ROOT)$(notdir $@)
		@echo "▶ Compiled minishell file: <$(notdir $<)>"
			
$(OBJ_ROOT)%.o:$(SRC_ROOT)executor/%.c $(BMLIB) $(MKF)
		@$(GCC) $(FLAGS) $(INCS) -c $< -o $(OBJ_ROOT)$(notdir $@)
		@echo "▶ Compiled minishell file: <$(notdir $<)>"

$(OBJ_ROOT)%.o:$(SRC_ROOT)utils/%.c $(BMLIB) $(MKF)
		@$(GCC) $(FLAGS) $(INCS) -c $< -o $(OBJ_ROOT)$(notdir $@)
		@echo "▶ Compiled minishell file: <$(notdir $<)>"

$(OBJ_ROOT)%.o:$(SRC_ROOT)buildin/%.c $(BMLIB) $(MKF)
		@$(GCC) $(FLAGS) $(INCS) -c $< -o $(OBJ_ROOT)$(notdir $@)
		@echo "▶ Compiled minishell file: <$(notdir $<)>"

-include $(DEPS)

.PHONY:	all bonus update clean fclean re