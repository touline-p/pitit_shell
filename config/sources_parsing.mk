# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_parsing.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 13:31:59 by twang             #+#    #+#              #
#    Updated: 2023/03/20 18:24:44 by wangthea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES	=	srcs/parsing/expands/expands.c 									\
			srcs/parsing/expands/cut_line.c 								\
			srcs/parsing/expands/replace_dollar_str_by_env_value.c			\
		#	srcs/main.c 	\
		#	mini_parsing.c \
		#	testing_utils.c \
		#	token_lst_utils.c \
		#	escaping_chars.c \
		#	preserv.c \
		#	simple_quoting.c \
		#	double_quoting.c \
		#	split_toklst_on_meta.c \
		#	split_on_meta.c \
		#	expand_variable.c \
		#	suppress_quotes.c \
		#	instruction_block_tree_utils.c \
		#	instruction_block_chain.c \
		#	instruction_block_tree_debug.c \
		#	str_token_debug.c \
		#	token_to_str_token.c \
		#	t_string_token_utils.c \
		#	init_pipe_arr_on.c \
		#	child_token.c \
		#	str_token_utils.c \
		#	instruction_block_building_utils.c \
		#	simple_tokens_utils.c \
		#	per_n_set_errno.c \
		#	get_here_doc_fd.c \
		#	read_here_doc_process.c \
