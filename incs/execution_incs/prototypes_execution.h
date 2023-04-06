/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_execution.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:38:27 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/06 23:34:45 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_EXECUTION_H
# define PROTOTYPES_EXECUTION_H

# include "structures_execution.h"
# include "structures_parsing.h"

/*----------------------------------------------------------------------------*/
/*---- Execution -------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

void	execution(t_string_token *string_of_tokens);

/*-- parsing -----------------------------------------------------------------*/

/*-- clean_utils --*/
void	clean_files_token(t_string_token *string_of_tokens);
void	clean_token(t_string_token *string_of_tokens);

/*-- infiles_manage --*/
void	infiles_management(t_data *data, t_string_token *string_of_tokens);

/*-- outfiles_manage --*/
void	outfiles_management(t_data *data, t_string_token *string_of_tokens);

/*-- string_manage --*/
void	strings_management(t_data *data, t_string_token *str_of_tok, char *str);

/*-- Genius Brieuc utils --*/
void	del_next_string_token(t_string_token *tok);
void	display_str_token(t_string_token *tok);

#endif