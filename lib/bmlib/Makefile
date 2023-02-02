# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 04:23:57 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/11/30 13:52:49 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------------------------- VAR DECLARATION ------------------------------ #

# Name value
NAME =			bmlib.a

# All the source of libft
SRC_LIB =	libraries/00_libft/ft_atoi.c				libraries/00_libft/ft_putchar_fd.c	\
			libraries/00_libft/ft_bzero.c				libraries/00_libft/ft_putendl_fd.c	\
			libraries/00_libft/ft_calloc.c				libraries/00_libft/ft_putnbr_fd.c	\
			libraries/00_libft/ft_isalnum.c				libraries/00_libft/ft_putstr_fd.c	\
			libraries/00_libft/ft_isalpha.c				libraries/00_libft/ft_split.c		\
			libraries/00_libft/ft_isascii.c				libraries/00_libft/ft_strchr.c		\
			libraries/00_libft/ft_isdigit.c				libraries/00_libft/ft_strdup.c		\
			libraries/00_libft/ft_isprint.c				libraries/00_libft/ft_striteri.c	\
			libraries/00_libft/ft_itoa.c				libraries/00_libft/ft_strjoin.c		\
			libraries/00_libft/ft_lstadd_back_bonus.c	libraries/00_libft/ft_strlcat.c		\
			libraries/00_libft/ft_lstadd_front_bonus.c	libraries/00_libft/ft_strlcpy.c		\
			libraries/00_libft/ft_lstclear_bonus.c		libraries/00_libft/ft_strlen.c		\
			libraries/00_libft/ft_lstdelone_bonus.c		libraries/00_libft/ft_strmapi.c		\
			libraries/00_libft/ft_lstiter_bonus.c		libraries/00_libft/ft_strncmp.c		\
			libraries/00_libft/ft_lstlast_bonus.c		libraries/00_libft/ft_strnstr.c		\
			libraries/00_libft/ft_lstmap_bonus.c		libraries/00_libft/ft_strrchr.c		\
			libraries/00_libft/ft_lstnew_bonus.c		libraries/00_libft/ft_strrspn.c		\
			libraries/00_libft/ft_lstsize_bonus.c		libraries/00_libft/ft_strspn.c		\
			libraries/00_libft/ft_memchr.c				libraries/00_libft/ft_strtrim.c		\
			libraries/00_libft/ft_memcmp.c				libraries/00_libft/ft_substr.c		\
			libraries/00_libft/ft_memcpy.c				libraries/00_libft/ft_tolower.c		\
			libraries/00_libft/ft_memmove.c				libraries/00_libft/ft_toupper.c		\
			libraries/00_libft/ft_memset.c				libraries/00_libft/ft_isspace.c

# All the source of ft_printf
SRC_PRI = 	libraries/01_ft_printf/ft_printf_bonus/a_ft_printf_bonus.c		\
			libraries/01_ft_printf/ft_printf_bonus/b_ft_read_bonus.c		\
			libraries/01_ft_printf/ft_printf_bonus/ft_10to16_bonus.c		\
			libraries/01_ft_printf/ft_printf_bonus/ft_a_convert_i_bonus.c	\
			libraries/01_ft_printf/ft_printf_bonus/ft_itoa_bonus.c			\
			libraries/01_ft_printf/ft_printf_bonus/ft_ptoa_bonus.c			\
			libraries/01_ft_printf/ft_printf_bonus/ft_putchar_bonus.c		\
			libraries/01_ft_printf/ft_printf_bonus/ft_putstr_bonus.c		\
			libraries/01_ft_printf/ft_printf_bonus/ft_uitoa_bonus.c

# All the source of gnl
SRC_GNL = 	libraries/gnl_for_bmlib/src/get_next_line.c	\
			libraries/gnl_for_bmlib/src/get_next_line_utils.c

# All the objects of libft
OBJS_LIB =		$(SRC_LIB:.c=.o)

# All the objects of ft_printf
OBJS_PRI =		$(SRC_PRI:.c=.o)

# All the objects of gnl
OBJS_GNL =		$(SRC_GNL:.c=.o)

# Header of bmlib
HEAD_BMLIB =	bmlib.h

# Header of libft
HEAD_LIB =		libraries/00_libft/libft.h

# Header of ft_printf
HEAD_PRF =		libraries/01_ft_printf/ft_printf_bonus/ft_printf_bonus.h

# Header of gnl
HEAD_GNL =		libraries/gnl_for_bmlib/src/get_next_line_bonus.h

# Git submodule update
GSU =			git submodule update

# Flags for GSU
GSU_FLAGS =		--remote --merge --recursive

# Variable to compile .c files
GCC =			gcc

# Flags for the gcc compilation
FLAGS =			-Wall -Werror -Wextra

# Library compilation
AR =			ar -rcs

# Remove variable
RM =			rm -f

# Makefile file
MKF =			Makefile

# Colors
DEL_LINE =		\033[2K
ITALIC =		\033[3m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
DARK_YELLOW =	\033[38;5;143m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
DARK_GREEN =	\033[1m\033[38;2;75;179;82m

# --------------------------------- ACTIONS ---------------------------------- #

# Main action of the makefile, checks for submodules updates and makes bmlib
all:
				@printf "$(DEF_COLOR)"
				@$(MAKE) $(NAME)

# Action to update the git submodules
update:
				@echo "$(DEF_COLOR)Updating submodules"
				@$(GSU) $(GSU_FLAGS)

# Clean all the .o files
clean:
				@$(RM) $(OBJS_LIB)
				@$(RM) $(OBJS_PRI)
				@$(RM) $(OBJS_GNL)
				@printf "$(DEF_COLOR)All objects of bmlib $(RED)removed $(DEF_COLOR)succesfully\n"

# Clean all the .o files and the bmlib.a
fclean:
				@$(RM) $(OBJS_LIB)
				@$(RM) $(OBJS_PRI)
				@$(RM) $(OBJS_GNL)
				@$(RM) $(NAME)
				@printf "$(DEF_COLOR)All bmlib $(RED)removed $(DEF_COLOR)\n"

# Clean all the .o files and the bmlib.a, and then restarts to the main action
re:
				@$(MAKE) fclean
				@$(MAKE) all

# Compiles all the .c files of libft
libraries/00_libft/%.o : libraries/00_libft/%.c $(HEAD_LIB) $(HEAD_BMLIB) $(MKF)
				@printf "$(DEL_LINE)\rlibft: .     [$(BROWN)$<$(DEF_COLOR)]"
				@$(GCC) $(FLAGS) -c $< -o $@

# Compiles all the .c files of ft_printf
libraries/01_ft_printf/ft_printf_bonus/%.o : libraries/01_ft_printf/ft_printf_bonus/%.c $(HEAD_PRF) $(HEAD_BMLIB) $(MKF)
				@printf "$(DEL_LINE)\rlibft:  .    [$(BROWN)$<$(DEF_COLOR)]"
				@$(GCC) $(FLAGS) -c $< -o $@

# Compiles all the .c files of gnl
libraries/gnl_for_bmlib/src/%.o : libraries/gnl_for_bmlib/src/%.c $(HEAD_GNL) $(HEAD_BMLIB) $(MKF)
				@printf "$(DEL_LINE)\rlibft:   .   [$(BROWN)$<$(DEF_COLOR)]"
				@$(GCC) $(FLAGS) -c $< -o $@

# Link action
$(NAME)::		$(OBJS_LIB) $(OBJS_PRI) $(OBJS_GNL)
				@printf "$(DEL_LINE)\r$(ITALIC)Linking...$(DEF_COLOR)"
				@$(AR) $@ $^
$(NAME)::
				@echo "$(DARK_GREEN)\rBMLIB COMPILED ✅$(DEF_COLOR)"

# Action names
.PHONY:			all update clean fclean re