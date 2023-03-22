/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:47:29 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/12 00:42:05 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PARSING_MINI_PARSING_H
# define MINI_PARSING_MINI_PARSING_H

# include "test_mini.h"

# include "basic_enums.h"
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>

t_token	*mini_parsing(char *str);
t_token	*token_lst_constructor(char *str);

/*** Token Utils ***/

void	token_lst_clear(t_token *trash);
t_token	*token_constructor(t_emt emt, char msg);
void	del_token(t_token *token);
void	del_next_token(t_token *token);
void	del_next_word(t_token *token);
t_ert	insert_str_in_tkn_lst(t_token *token_lst, char *str, t_esec essec);
int		len_to_next_type(t_token *pin);

/*** t_emt utils ***/

t_ert	is_control_operator(t_emt token);

/*** preserving ***/

typedef t_ert	(*t_preserv_act)(t_token *first, t_token *second, t_token **ref);

t_ert	preserve_token_lst(t_token *token);
t_ert 	escaping_chars(t_token *tok);
t_ert	escape_process(t_token *last_pt, t_token *tok, t_token **voided);
t_ert	dquoting_process(t_token *voided, t_token *last_token, t_token **end_of_quot_pt);
t_ert	squoting_process(t_token *voided, t_token *token, t_token **end_of_quot_pt);

/*** split on meta ***/

t_token	*split_toklst_on_meta(t_token *tok);
t_token	*regroup_meta(t_token *tok);
t_token	*split_on_meta(t_token *tok);

/*** expand on dollars ***/

t_ert	expand_dollars(t_token *token_lst, char **env);


void	suppress_quotes(t_token *tok);


t_token	*get_next_emt(t_token *tok);



void						instruction_block_tree_destructor(t_instruction_block_tree *trash);
t_instruction_block_tree	*instruction_block_tree_constructor(void);
t_ert						instruction_block_tree_constructor_on(t_instruction_block_tree **t_instr_pt);

/*** String token ***/
t_string_token	*string_token_creator(void);
t_ert			string_token_creator_on(t_string_token **tok_pt);
t_string_token *token_lst_to_str_token(t_token *tok);
void			string_token_destructor(t_string_token *trash);
void			cpy_token_lst_to_str(t_token *tok, char *str);
int				next_control_operator_is_a_pipe(t_string_token *tok);
void			del_next_string_token(t_string_token *tok);
void			del_space_token(t_string_token *tok);

/*** Block instruction ***/

t_ert	allocate_first_child_on(t_string_token **str_tok_pt, t_instruction_block_tree **block_pt, int **pipe_arr, char **env);
t_ert	init_pipe_arr_on(int ***pipe_arr_pt, t_string_token *tok);
t_ert	str_token_to_instruction_block_tree_on(t_string_token *tok, t_instruction_block_tree **tree_pt);

/*** build block ***/

t_ert	stock_last_redirect(t_instruction_block_tree *block, t_string_token *tok, char **env);

void	per_n_set_errno(char *msg);

#endif //MINI_PARSING_MINI_PARSING_H
