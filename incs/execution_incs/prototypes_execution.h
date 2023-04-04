/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_execution.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:38:27 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/04 18:46:33 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_EXECUTION_H
# define PROTOTYPES_EXECUTION_H

# include "structures_execution.h"
# include "structures_parsing.h"

/*-- execution----------------------------------------------------------------*/

void	execution(t_string_token *string_of_tokens);

void	token_recognition(t_data *data, t_string_token *string_of_tokens);

void	heredoc_management(t_data *data, char *limiter);
void	files_management(t_data *data, char *file, t_token_minishell token);
void	strings_management(t_data *data, char *string);

void	clean_files_token(t_string_token *string_of_tokens);
void	clean_token(t_string_token *string_of_tokens);

void	del_next_string_token(t_string_token *tok);
void	display_str_token(t_string_token *tok);

#endif