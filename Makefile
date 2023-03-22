# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twang <twang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 14:09:46 by twang             #+#    #+#              #
#    Updated: 2023/03/22 14:12:48 by twang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config/print.mk
include config/headers_execution.mk
include config/headers_parsing.mk
include config/sources_execution.mk
include config/sources_parsing.mk

.SILENT:

#--variables-------------------------------------------------------------------#

NAME		=	minishell
DEBUG		=	no

#--includes & libraries--------------------------------------------------------#

INC_DIR		=	incs
LIBFT_DIR	=	libft

#--sources & objects-----------------------------------------------------------#

SRC_DIR		=	srcs
OBJ_DIR		=	.objs

#--flags-----------------------------------------------------------------------#

CFLAGS		=	-Wall -Wextra -Werror -I $(LIBFT_DIR) -I $(INC_DIR)/execution_incs -I $(INC_DIR)/parsing_incs

#--debug flags--------------------------------------------------------#

DFLAGS		=	-g3 -fsanitize=address

ifeq ($(DEBUG), yes)
CFLAGS 		+=	$(DFLAGS)
endif

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
	$(CC) $^ $(CFLAGS) $(LIBFT) -o $@
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

#--print header----------------------------------------------------------------#

header:
	printf "\n${PURPLE}project:\t${END}${BLUE}minishell${END}\n"
	printf "${PURPLE}author:\t\t${END}${BLUE}bpoumeau && twang${END}\n"
	printf "${PURPLE}debug mode:\t${END}${BLUE}${DEBUG}${END}\n"
	printf "${PURPLE}compiler:\t${END}${BLUE}${CC}${END}\n"
	printf "${PURPLE}flags:\t\t${END}${BLUE}${CFLAGS}${END}\n"
	printf "${PURPLE}date:\t\t${END}${BLUE}2023/03/20${END}\n"
	printf "              ____________________________\n\n"

#--re, clean & fclean----------------------------------------------------------#

re:
	$(MAKE) fclean
	$(MAKE) all

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -rf $(OBJECTS)
	$(PRINT_CLEAN)

fclean:
	$(MAKE) clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(PRINT_FCLEAN)

#--PHONY-----------------------------------------------------------------------#

.PHONY: all lib debug re clean fclean
 