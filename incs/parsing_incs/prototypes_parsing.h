/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_parsing.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:38:27 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/17 14:47:15 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef PROTOTYPES_PARSING_H
// # define PROTOTYPES_PARSING_H

// # include "minishell_parsing.h"
// # include <stddef.h>
// # include <stdlib.h>
// # include <stdbool.h>
// # include <unistd.h>
// # include <errno.h>
// # include <fcntl.h>
// # include "../execution_incs/minishell_execution.h"

// /*----- expands --------------------------------------------------------------*/

// //cut_line.c
// t_return_status	cut_line_on(char *line, char ***res_pt);

// //expands.c
// t_return_status	performe_expand_on_line(char **line_pt, char **env);

// //replace_dollar_str_by_env_value.c
// t_return_status	replace_dollar_str_by_env_value(char **pin_pt, char **env);

// /*----- expands --------------------------------------------------------------*/

// # ifndef MINI_PARSING_MINI_PARSING_H
// #  define MINI_PARSING_MINI_PARSING_H

// t_token			*mini_parsing(char *str);
// t_token			*token_lst_constructor(char *str);

// /*** Token Utils ***/

// void			token_lst_clear(t_token *trash);
// t_token			*token_constructor(t_emt emt, char msg);
// void			del_token(t_token *token);
// void			del_next_token(t_token *token);
// void			del_next_word(t_token *token);
// t_return_status	insert_str_in_tkn_lst(t_token *token_lst, \
// 								char *str, t_esec essec);
// int				len_to_next_type(t_token *pin);
// t_token			*token_constructor_esec(t_emt emt, char msg, t_esec esec);

// /*** t_emt utils ***/

// t_return_status	is_control_operator(t_emt token);

// /*** preserving ***/

// //// typedef t_return_status	(*t_preserv_act)(t_token *first, \
// 								t_token *second, t_token **ref);

// t_return_status	preserve_token_lst(t_token *token);
// t_return_status	escaping_chars(t_token *tok);
// t_return_status	escape_process(t_token *last_pt, \
// 								t_token *tok, t_token **voided);
// t_return_status	dquoting_process(t_token *voided, \
// 								t_token *last_token, \
// 								t_token **end_of_quot_pt);
// t_return_status	squoting_process(t_token *voided, \
// 								t_token *token, t_token **end_of_quot_pt);

// /*** split on meta ***/
// t_token			*split_toklst_on_meta(t_token *tok);
// t_token			*regroup_meta(t_token *tok);
// t_token			*split_on_meta(t_token *tok);

// /*** expand on dollars ***/
// t_return_status	expand_dollars(t_token *token_lst, char **env);
// void			suppress_quotes(t_token *tok);
// t_token			*get_next_emt(t_token *tok);

// /*** String token ***/
// t_string_token	*string_token_creator(void);
// t_return_status	string_token_creator_on(t_string_token **tok_pt);
// t_string_token	*token_lst_to_str_token(t_token *tok);
// void			string_token_destructor(t_string_token *trash);
// void			cpy_token_lst_to_str(t_token *tok, char *str);
// int				next_control_operator_is_a_pipe(t_string_token *tok);
// void			del_next_string_token(t_string_token *tok);
// void			del_space_token(t_string_token *tok);
// t_return_status	split_t_string_token_on_space(t_string_token **token_pt);
// void			del_empty_tokens(t_string_token *token_lst);
// void			free_all_str(t_data *data);

// /*** checking syntax ***/
// t_return_status	syntax_is_valid(t_string_token *lst_to_check);

// /*** env_utils ***/
// ////typedef t_return_status	(*t_export_ft)(char *arg, char ***env_pt);

// t_return_status	env_init_on(char ***env_pt);
// char			*get_line_from_key(char *key, char **env);
// bool			is_a_key_from_env(char *key, char **env);
// char			*get_env_content_from_key(char *key, char **env);
// t_return_status	add_str_to_env(char *line, char ***env_pt);
// t_return_status	del_str_from_env(char *line, char ***env_pt);
// void			display_str_par(t_string_token *tok);
// size_t			go_to_next_(t_emt token, t_string_token *tmp, \
// 								t_string_token **str_tok);

// char			*get_first_line_in_env(char **env);
// char			*get_next_line_in_env(char *last, char **env);
// char			**get_line_addr_from_key(char *key, char **env);
// void			replace_content_in_env(char *line, char **env);
// bool			has_a_key_from_env(char *line, char **env);

// t_return_status	expand_for_args(t_string_token *token_lst, char **env);

// t_return_status	cut_all_lines(t_string_token *string_token_lst);
// t_return_status	join_all_lines(t_string_token *string_token_lst, char **env);
// t_return_status	join_arr_on(char **str_arr, char **line_pt, char **env);

// void			per_n_set_errno(char *msg);
// bool			file_is_empty(char *file);

// void			display_tokens(t_token *token_lst);
// void			display_t_emt(t_token *token);
// void			put_esec(t_token *tok);
// void			display_str_token(t_string_token *tok);
// void			display_str_token_till(t_string_token *tok);
// char			*_get_env_variable(t_token *token, char **env);
// void			cpy_next_char(unsigned int index, char *str);
// t_return_status	replace_dquotes_str_by_env_value(char **line_pt, char **env);
// t_return_status	get_lexed_str_token_lst_from_line(char *line, \
// 						t_string_token **str_tok_pt, char **env);

// void			update_tokens(t_string_token *str_tok_lst);
// bool			is_a_redir(t_emt token);

// /***	bonus	***/
// void			go_to_next_logical_door(t_string_token *src, \
// 											t_string_token **dst);
// char			*format_string_token(t_string_token *token);
// void			check_par_err(t_string_token *str_tok_lst);

// # endif
// #endif //MINI_PARSING_MINI_PARSING_H
