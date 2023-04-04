# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twang <twang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 14:09:46 by twang             #+#    #+#              #
#    Updated: 2023/04/02 20:40:46 by bpoumeau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config/headers_execution.mk
include config/headers_parsing.mk
include config/print.mk
include config/sources_execution.mk
include config/sources_parsing.mk

.SILENT:

#--variables-------------------------------------------------------------------#

NAME		=	minishell
DEBUG		=	no

BPOUMEAU	=	\e]8;;https://profile.intra.42.fr/users/bpoumeau\a\e[34mbpoumeau\e[34m\e]8;;\a
TWANG		=	\e]8;;https://profile.intra.42.fr/users/twang\a\e[34mtwang\e[34m\e]8;;\a

#--includes & libraries--------------------------------------------------------#

INC_DIR		=	incs
LIBFT_DIR	=	libft

#--sources & objects-----------------------------------------------------------#

SRC_DIR		=	srcs
OBJ_DIR		=	.objs

#--flags-----------------------------------------------------------------------#

CFLAGS		=	-Wall -Wextra -Werror -I $(LIBFT_DIR) -I $(INC_DIR)/execution_incs -I $(INC_DIR)/parsing_incs -g3

#--debug flags--------------------------------------------------------#

DFLAGS		=	-g3 -fsanitize=address

ifeq ($(DEBUG), yes)
CFLAGS 		+=	$(DFLAGS)
endif

#--leaks flags--------------------------------------------------------#

LEAKS	=	valgrind --leak-check=full --track-fds=yes

#--libs------------------------------------------------------------------------#

LIBFT	=	$(LIBFT_DIR)/libft.a

#--objects---------------------------------------------------------------------#

OBJECTS	=	$(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

#--global rules----------------------------------------------------------------#

.DEFAULT_GOAL = all

#--compilation rules-----------------------------------------------------------#

all:
	$(MAKE) header
	$(MAKE) lib
	$(MAKE) $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $^ $(CFLAGS) $(LIBFT) -o $@ -lreadline
	$(PRINT_CREATING)

$(OBJ_DIR)/%.o: %.c $(HEADERS) $(LIBFT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	$(PRINT_COMPILING)

#--libs, debugs & bonus--------------------------------------------------------#

lib:
	$(MAKE) -C $(LIBFT_DIR)

debug:
	$(MAKE) re DEBUG=yes

leaks:
	clear
	$(MAKE) re
	$(LEAKS) ./minishell

#--print header----------------------------------------------------------------#

header:
	printf "\n${PURPLE}project:\t${END}${BLUE}minishell${END}\n"
	printf "${PURPLE}author:\t\t${END}${BLUE}${BPOUMEAU} && ${TWANG}${END}\n"
	printf "${PURPLE}debug mode:\t${END}${BLUE}${DEBUG}${END}\n"
	printf "${PURPLE}compiler:\t${END}${BLUE}${CC}${END}\n"
	printf "${PURPLE}flags:\t\t${END}${BLUE}${CFLAGS}${END}\n"
	printf "${PURPLE}date:\t\t${END}${BLUE}2023/03/20${END}\n"
	printf "              ____________________________\n\n"

#--re, clean & fclean----------------------------------------------------------#

re:
	clear
	$(MAKE) fclean
	$(MAKE) all

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -rf $(OBJECTS)
	$(PRINT_CLEAN)

fclean:
	clear
	$(MAKE) clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(PRINT_FCLEAN)

#--PHONY-----------------------------------------------------------------------#

.PHONY: all lib debug re clean fclean
 
