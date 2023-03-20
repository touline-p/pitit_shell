# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twang <twang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 14:09:46 by twang             #+#    #+#              #
#    Updated: 2023/03/20 17:10:14 by twang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

include config/headers_execution.mk
include config/headers_parsing.mk
include config/sources_execution.mk
include config/sources_parsing.mk

#--variables-------------------------------------------------------------------#

NAME		=	minishell
DEBUG		=	no

#--includes & libraries--------------------------------------------------------#

INC_DIR		=	includes
LIBFT_DIR	=	$(LIB_DIR)/libft

#--sources & objects-----------------------------------------------------------#

SRC_DIR		=	srcs
OBJ_DIR		=	.objs

#--flags-----------------------------------------------------------------------#

CFLAGS		=	-Wall -Wextra -Werror -I $(LIBFT_DIR) -I $(INC_DIR)

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

$(OBJ_DIR)/%.o: %.c $(HEADERS) $(LIBFT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@



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

fclean:
	$(MAKE) clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

#--PHONY-----------------------------------------------------------------------#

.PHONY: all lib debug re clean fclean
 