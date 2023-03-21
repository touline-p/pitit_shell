# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twang <twang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 14:09:46 by twang             #+#    #+#              #
#    Updated: 2023/03/21 17:39:21 by twang            ###   ########.fr        #
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
 