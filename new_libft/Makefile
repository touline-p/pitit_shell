# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twang <twang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 19:11:08 by twang             #+#    #+#              #
#    Updated: 2023/04/13 19:32:20 by twang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include libft_sources.mk
include libft_headers.mk
include print_libft.mk

.SILENT:

#-- executable file -----------------------------------------------------------#

NAME	= libft.a

#-- files directories ---------------------------------------------------------#

INC_DIR		=	incs
SRC_DIR		=	srcs
OBJ_DIR		=	.objs

#-- objects -------------------------------------------------------------------#

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

#-- flags ---------------------------------------------------------------------#

CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR)

#-- global rules --------------------------------------------------------------#

all :	$(NAME)

$(NAME) : $(OBJECTS)
	$(AR) rcs $@ $^
	$(PRINT_CREATING)

$(OBJ_DIR)/%.o : %.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	$(PRINT_COMPILING)

#-- clean rules ---------------------------------------------------------------#

clean :
	$(RM) $(OBJECTS)
	$(PRINT_CLEAN)

fclean : 
	clear
	$(MAKE) clean 
	$(RM) $(NAME)
	$(PRINT_FCLEAN)

re : 
	clear
	$(MAKE) fclean
	$(MAKE) all

#-- phony ---------------------------------------------------------------------#

.PHONY: all clean fclean re
