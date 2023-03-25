/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_parsing.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:38:27 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/20 19:20:56 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PROTOTYPES_PARSING_H
# define PROTOTYPES_PARSING_H

# include "enums_parsing.h"
# include "libft.h"
# include "structures_parsing.h"
# include "structures_execution.h"

/*----- expands --------------------------------------------------------------*/

//cut_line.c
t_return_status	cut_line_on(char *line, char ***res_pt);

//expands.c
t_return_status	performe_expand_on_line(char **line_pt, char **env);

//replace_dollar_str_by_env_value.c
t_return_status	replace_dollar_str_by_env_value(char **pin_pt, char **env);

/*----- expands --------------------------------------------------------------*/

#ifndef MINI_PARSING_MINI_PARSING_H
# define MINI_PARSING_MINI_PARSING_H


# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
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
t_return_status 	insert_str_in_tkn_lst(t_token *token_lst, char *str, t_esec essec);
int		len_to_next_type(t_token *pin);

/*** t_emt utils ***/

t_return_status is_control_operator(t_emt token);

/*** preserving ***/

typedef t_return_status	(*t_preserv_act)(t_token *first, t_token *second, t_token **ref);

t_return_status 	preserve_token_lst(t_token *token);
t_return_status		escaping_chars(t_token *tok);
t_return_status		escape_process(t_token *last_pt, t_token *tok, t_token **voided);
t_return_status		dquoting_process(t_token *voided, t_token *last_token, t_token **end_of_quot_pt);
t_return_status		squoting_process(t_token *voided, t_token *token, t_token **end_of_quot_pt);

/*** split on meta ***/

t_token	*split_toklst_on_meta(t_token *tok);
t_token	*regroup_meta(t_token *tok);
t_token	*split_on_meta(t_token *tok);

/*** expand on dollars ***/

t_return_status 	expand_dollars(t_token *token_lst, char **env);
void	suppress_quotes(t_token *tok);
t_token	*get_next_emt(t_token *tok);

/*** String token ***/
t_string_token	*string_token_creator(void);
t_return_status 			string_token_creator_on(t_string_token **tok_pt);
t_string_token *token_lst_to_str_token(t_token *tok);
void			string_token_destructor(t_string_token *trash);
void			cpy_token_lst_to_str(t_token *tok, char *str);
int				next_control_operator_is_a_pipe(t_string_token *tok);
void			del_next_string_token(t_string_token *tok);
void			del_space_token(t_string_token *tok);

/*** build block ***/

void	per_n_set_errno(char *msg);

#ifndef TEST_MINI_H
# define TEST_MINI_H

void	display_tokens(t_token *token_lst);
void	display_t_emt(t_token *token);
void	put_esec(t_token *tok);



char	*_get_env_variable(t_token *token, char **env);

#endif
#endif //MINI_PARSING_MINI_PARSING_H
#endif
