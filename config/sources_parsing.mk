# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_parsing.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twang <twang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 13:31:59 by twang             #+#    #+#              #
#    Updated: 2023/05/12 22:20:26 by bpoumeau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES +=	srcs/parsing/expands/cut_line.c 								\
			srcs/parsing/expands/expands.c 									\
			srcs/parsing/expands/replace_dollar_str_by_env_value.c			\
			srcs/token_lst/token_lst_constructor.c 							\
			srcs/parsing/expands/replace_dollar_str_by_env_value.c			\
			srcs/parsing/expands/cut_line.c 								\
			srcs/parsing/expands/expands.c 									\
			srcs/bonus/switchman.c											\
			srcs/bonus/subshell_preparation.c								\
			srcs/parsing/expands/cut_all_lines.c 							\
			srcs/parsing/expands/replace_dquotes_str_by_env_value.c			\
			srcs/parsing/expands/join_expands.c 							\
			srcs/lexing_parsing/5_suppress_quotes/suppress_quotes.c			\
			srcs/lexing_parsing/3_expand_in_parsing/expand_variable.c		\
			srcs/lexing_parsing/parsing_articulation.c						\
			srcs/lexing_parsing/check_unic_syntax.c							\
			srcs/lexing_parsing/1_preservation/double_quoting.c 			\
			srcs/lexing_parsing/1_preservation/escaping_chars.c 			\
			srcs/lexing_parsing/1_preservation/preserv.c 					\
			srcs/lexing_parsing/1_preservation/simple_quoting.c 			\
			srcs/lexing_parsing/2_metachar_managing/split_toklst_on_meta.c	\
			srcs/lexing_parsing/2_metachar_managing/split_on_meta.c			\
			srcs/lexing_parsing/parsing_token_utils/simple_tokens_utils.c	\
			srcs/lexing_parsing/parsing_token_utils/token_lst_utils.c		\
			srcs/lexing_parsing/parsing_token_utils/token_lst_utils_2.c		\
			srcs/lexing_parsing/parsing_token_utils/testing_utils.c			\
			srcs/lexing_parsing/syntax_is_valid.c							\
			srcs/lexing_parsing/check_par_err.c								\
			srcs/t_string_token_utils/t_string_token_utils.c				\
			srcs/t_string_token_utils/str_token_debug.c						\
			srcs/t_string_token_utils/token_to_str_token.c					\
			srcs/t_string_token_utils/str_token_utils.c						\
			srcs/builtin/export.c 											\
			srcs/initialisation/env_init.c									\
			srcs/main.c														\
			srcs/main_utils.c												\
			srcs/builtin/env_utils/ordering_env_export.c					\
			srcs/builtin/env_utils/env_utils.c								\
			srcs/builtin/env_utils/get_in_env.c								\
			srcs/builtin/env.c												\
			srcs/builtin/exit.c												\
			srcs/builtin/cd.c												\
			srcs/builtin/echo.c												\
			srcs/builtin/pwd.c												\
			srcs/builtin/unset.c											\
			srcs/builtin/export.c											\
			srcs/builtin/export_get_ft_to_do.c								\
			srcs/builtin/switchman_once.c									\


