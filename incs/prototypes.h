/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:25:03 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 11:29:25 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/*----------------------------------------------------------------------------*/

t_return_status	cut_line_on(char *line, char ***res_pt);
t_return_status	performe_expand_on_line(char **line_pt, char **env);
t_return_status	replace_dollar_str_by_env_value(char **pin_pt, char **env);

/*----------------------------------------------------------------------------*/

t_token			*mini_parsing(char *str);
t_token			*token_lst_constructor(char *str);
void			token_lst_clear(t_token *trash);
t_token			*token_constructor(t_emt emt, char msg);
void			del_token(t_token *token);
void			del_next_token(t_token *token);
void			del_next_word(t_token *token);
t_return_status	insert_str_in_tkn_lst(t_token *token_lst, \
								char *str, t_esec essec);
int				len_to_next_type(t_token *pin);
t_token			*token_constructor_esec(t_emt emt, char msg, t_esec esec);


#endif