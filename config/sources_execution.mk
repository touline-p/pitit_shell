# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_execution.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twang <twang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 13:31:59 by twang             #+#    #+#              #
#    Updated: 2023/04/24 10:58:13 by twang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES	=																	\
			srcs/execution/execve/childs.c									\
			srcs/execution/execve/fds_manage.c								\
			srcs/execution/parsing/clean_utils.c							\
			srcs/execution/parsing/infiles_manage.c							\
			srcs/execution/parsing/outfiles_manage.c						\
			srcs/execution/parsing/strings_manage.c							\
			srcs/execution/utils/cmds_utils.c								\
			srcs/execution/utils/files_utils.c								\
			srcs/execution/utils/path_utils.c								\
			srcs/execution/utils/struct_utils.c								\
			srcs/execution/execution.c										\
			srcs/signals/signals.c											\
			srcs/debug_folder/debug_fonction.c
