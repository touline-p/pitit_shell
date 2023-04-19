/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_execution.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:38:27 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/19 15:24:20 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_EXECUTION_H
# define PROTOTYPES_EXECUTION_H

# include "libft.h"
# include "structures_execution.h"
# include "structures_parsing.h"

/*----------------------------------------------------------------------------*/
/*---- Execution -------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

void	execution(t_string_token *lst_of_tok, char ***env);


/*-- execve ------------------------------------------------------------------*/

/*-- childs --*/
t_return_status	childs_execve(t_data *data, char **env);

/*-- fds_manage --*/
void	close_fds(t_data *data, int block_id);
void	close_all_fds(t_data *data, int block_id);
void	duplicate_fds(t_data *data, int block_id);

/*-- parsing -----------------------------------------------------------------*/

/*-- clean_utils --*/
void	clean_files_token(t_string_token *lst_of_tok);
void	clean_token(t_string_token *lst_of_tok);

/*-- infiles_manage --*/
void	infiles_management(t_data *data, t_string_token *lst_of_tok);

/*-- outfiles_manage --*/
void	outfiles_management(t_data *data, t_string_token *lst_of_tok);

/*-- string_manage --*/
void	strings_management(t_data *data, t_string_token *lst_of_tok, char **env_pt);

/*-- utils -------------------------------------------------------------------*/

/*-- cmds_utils --*/
t_builtin		is_builtin(char *string);
t_return_status	builtin_switch(t_builtin builtin, char **av, char ***env_pt);

/*-- files_utils --*/
void	check_opened_infiles(t_data *data, int block_id);
void	check_opened_outfiles(t_data *data, int block_id);

/*-- path_utils --*/
int		get_path_size(char **paths);
char	**get_paths(char **env);

/*-- struct_utils --*/
void	free_commands(t_data *data);

/*-- Genius Brieuc utils --*/
void	string_token_destructor(t_string_token *trash);
void	del_next_string_token(t_string_token *tok);
void	display_str_token(t_string_token *tok);
void	display_t_emt_string(t_string_token *token);
char 	**join_token_lst(t_string_token **arg);
t_return_status	expand_for_args(t_string_token *token_lst, char **env);


/*-- debug --*/
void    print_pid(int pid);
void    print_fd(char *msg, int fd);
void    print_is_heredoc(bool is);
void    print_builtin(t_builtin built);
void    print_cmd_block(t_cmd cmd);

/*-- Builtin --*/
t_return_status	cd_builtin(char **av, char ***env_pt);
t_return_status export_builtin(char **av, char ***env_pt);
t_return_status	env_builtin(char **av, char ***env_pt);
t_return_status	pwd_builtin(char **av, char ***env_pt);
t_return_status	unset_builtin(char **av, char ***env_pt);
t_return_status	echo_builtin(char **av, char ***env_pt);

#endif