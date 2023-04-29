# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    print_libft.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twang <twang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 19:32:01 by twang             #+#    #+#              #
#    Updated: 2023/04/13 19:32:03 by twang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##    ~~    Colors -------------------------------------------------------------

GREY		=	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
ORANGE		=	\033[33m
BLUE		=	\033[34m
PURPLE		=	\033[35m
LIGHTBLUE	=	\033[36m
WHITE		=	\033[37m

##    ~~    Styles -------------------------------------------------------------

END			=	\033[0m
BOLD		=	\033[1m
ITALIC		=	\033[3m
UNDERLINE	=	\033[4m
DEL_LINE	=	\033[2K\r

##    ~~    Prints -------------------------------------------------------------

define    PRINT_CLEAN
    printf "[ ${RED}removing${END} ]\t${LIGHTBLUE}libft's binaries files${END}\n"
endef

define    PRINT_FCLEAN
    printf "[ ${RED}removing${END} ]\t${LIGHTBLUE}libft's executable file${END}\n"
endef

define    PRINT_COMPILING
    printf "%-95b%b" "[ ${PURPLE}compiling${END} ]\t${LIGHTBLUE}$<${END}" "${GREEN}[✓]${END}\n"
endef

define    PRINT_CREATING
    printf "\n[ ${PURPLE}creating${END} ]\t${LIGHTBLUE}$@${END}\n\n"
endef

define LINE
    printf "\n              ----------------------------\n\n"
endef