/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_execution.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:38:27 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/12 17:17:49 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_EXECUTION_H
# define PROTOTYPES_EXECUTION_H

# include "libft.h"
# include "structures_execution.h"
# include "structures_parsing.h"

/*----------------------------------------------------------------------------*/
/*---- Bonus -----------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- wildcards ---------------------------------------------------------------*/

/*-- wildcards_utils --*/
t_return_status	check_line(char *line);
int				get_alloc_size(char *line);
t_return_status	fill_dst_arr(char *line, char **arr_to_fill);

/*-- wildcards --*/
t_return_status	expand_wildcards(char ***original_pt);

/*----------------------------------------------------------------------------*/
/*---- Execution -------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

void	execution(t_data *data, t_string_token *lst_of_tok, char ***env_pt);

/*-- execve ------------------------------------------------------------------*/

void			replace_space_by_minus(unsigned int nb, char *content);

/*-- childs --*/
t_return_status	childs_execve(t_data *data, char ***env);

/*-- fds_manage --*/
t_return_status	heredoc_management(t_data *data, t_string_token *str_tok_lst, char **env);
t_return_status check_unic_syntax(t_string_token *actual, bool *string, t_pr_stat *in_parentheses);
void			close_fds(t_data *data, int block_id);
void			close_all_fds(t_data *data, int block_id);
t_return_status	duplicate_fds(t_cmd block, t_data *data, char ***env_pt);

/*-- parsing -----------------------------------------------------------------*/

/*-- clean_utils --*/
void			clean_files_token(t_string_token *lst_of_tok);
void			clean_token(t_string_token *lst_of_tok);

/*-- infiles_manage --*/
t_return_status	infiles_management(t_data *data, t_string_token *lst_of_tok, \
						char **env);

/*-- outfiles_manage --*/
t_return_status	outfiles_management(t_data *data, t_string_token *lst_of_tok, \
						char **env);

/*-- string_manage --*/
void			strings_management(t_data *data, t_string_token *lst_of_tok, \
						char **env_pt);

/*-- utils -------------------------------------------------------------------*/

/*-- cmds_utils --*/
t_builtin		is_builtin(char *string);
t_return_status	builtin_switch(t_builtin builtin, char **av, char ***env_pt);

/*-- files_utils --*/
void			check_opened_infiles(t_data *data, int block_id);
void			check_opened_outfiles(t_data *data, int block_id);
t_return_status	redirection_syntax_error(char *str);

/*-- path_utils --*/
int				get_path_size(char **paths);
char			**get_paths(char **env);
bool			is_path(char *line);
bool			is_cmd(char *line);

/*-- struct_utils --*/
void			free_commands(t_data *data);

/*----------------------------------------------------------------------------*/
/*---- Signals ---------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- signals --*/
void			init_signals(void);
void			handle_signal_child(int signal);
void			handle_signal_heredoc(int signal);
void			handle_signal_heredoc_sigquit(int signal);
void			handle_signal_father_process(int signal);

/*-- Genius Brieuc utils --*/
void			string_token_destructor(t_string_token *trash);
void			del_next_string_token(t_string_token *tok);
void			display_str_token(t_string_token *tok);
void			display_t_emt_string(t_string_token *token);
char			**join_token_lst(t_string_token **arg, char **env);
void			manage_ambiguous(t_cmd *cmd, char *file);
t_return_status	expand_for_args(t_string_token *token_lst, char **env);
t_return_status	switchman(t_data *data, \
						t_string_token *token_lst, char ***env_pt);
void			ft_free_all_str_lst(t_data *data, int index);
t_return_status	read_fd_in_str(int fd, char **dst);
t_return_status	heredoc_child_management(t_cmd *cmd, \
						t_data *data, char **env_pt);
char	**subshell_preparation(t_string_token **start);

/*----------------------------------------------------------------------------*/
/*---- Main ------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- main_utils --*/
t_return_status	check_arguments(int ac, char **av);
void			clean_the_prompt(char *prompt, char *line, char **env);

/*-- debug --*/
void			print_pid(int pid);
void			print_fd(char *msg, int fd);
void			print_is_heredoc(bool is);
void			print_builtin(t_builtin built);
void			print_cmd_block(char *msg, t_cmd cmd);

/*-- Builtin --*/
t_return_status	switchman_once(t_data *data, char ***env_pt);
t_return_status	cd_builtin(char **av, char ***env_pt);
t_return_status	export_builtin(char **av, char ***env_pt);
t_return_status	env_builtin(char **av, char ***env_pt);
t_return_status	pwd_builtin(char **av, char ***env_pt);
t_return_status	unset_builtin(char **av, char ***env_pt);
t_return_status	echo_builtin(char **av, char ***env_pt);
t_return_status	exit_builtin(char **av, char ***env_pt);

#endif