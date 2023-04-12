/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_execution.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:38:27 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/12 19:24:15 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_EXECUTION_H
# define PROTOTYPES_EXECUTION_H

# include "structures_execution.h"
# include "structures_parsing.h"

/*----------------------------------------------------------------------------*/
/*---- Execution -------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

void	execution(t_string_token *str_of_tok, char ***env);

/*-- parsing -----------------------------------------------------------------*/

/*-- clean_utils --*/
void	clean_files_token(t_string_token *str_of_tok);
void	clean_token(t_string_token *str_of_tok);

/*-- infiles_manage --*/
void	infiles_management(t_data *data, t_string_token *str_of_tok);

/*-- outfiles_manage --*/
void	outfiles_management(t_data *data, t_string_token *str_of_tok);

/*-- string_manage --*/
void	strings_management(t_data *data, t_string_token *str_of_tok, char **env_pt);

/*-- utils -------------------------------------------------------------------*/

/*-- cmds_utils --*/
t_builtin	is_builtin(char *string);

/*-- path_utils --*/


/*-- Genius Brieuc utils --*/
void	string_token_destructor(t_string_token *trash);
void	del_next_string_token(t_string_token *tok);
void	display_str_token(t_string_token *tok);
void	display_t_emt_string(t_string_token *token);

/*-- Builtin --*/

t_return_status	builtin_switchman(t_builtin builtin, char **av, char ***env_pt);
t_return_status	cd_builtin(char **av, char ***env_pt);
t_return_status export_builtin(char **av, char ***env_pt);
t_return_status	env_builtin(char **av, char ***env_pt);
t_return_status	pwd_builtin(char **av, char ***env_pt);
t_return_status	unset_builtin(char **av, char ***env_pt);
t_return_status	echo_builtin(char **av, char ***env_pt);

#endif