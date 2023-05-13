/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:07:11 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/14 00:47:09 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/*---- headers ---------------------------------------------------------------*/

# include "libft.h"
# include "structures.h"

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

/*-- subshell_preparation --*/
char	**subshell_preparation(t_string_token **start);

/*-- switchman --*/
t_return_status	switchman(t_data *data, \
						t_string_token *token_lst, char ***env_pt);
						
/*----------------------------------------------------------------------------*/
/*---- Builtin ---------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- env_utils ---------------------------------------------------------------*/

/*-- env_utils --*/
/*-- get_in_env --*/
/*-- ordering_env_export --*/

/*-- cd --*/
t_return_status	cd_builtin(char **av, char ***env_pt);

/*-- echo --*/
t_return_status	echo_builtin(char **av, char ***env_pt);

/*-- env --*/
t_return_status	env_builtin(char **av, char ***env_pt);

/*-- exit --*/
t_return_status	exit_builtin(char **av, char ***env_pt);

/*-- export_get_ft_to_do --*/
/*-- export --*/
t_return_status	export_builtin(char **av, char ***env_pt);

/*-- pwd --*/
t_return_status	pwd_builtin(char **av, char ***env_pt);

/*-- switchman_once --*/
t_return_status	switchman_once(t_data *data, char ***env_pt);

/*-- unset --*/
t_return_status	unset_builtin(char **av, char ***env_pt);

/*----------------------------------------------------------------------------*/
/*---- Execution -------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- execve ------------------------------------------------------------------*/

/*-- childs --*/
t_return_status	childs_execve(t_data *data, char ***env);

/*-- fds_manage --*/
t_return_status	heredoc_management(t_data *data, t_string_token *str_tok_lst, char **env);
t_return_status check_unic_syntax(t_string_token *actual, bool *string, t_pr_stat *in_parentheses);
void			close_fds(t_data *data, int block_id);
void			close_all_fds(t_data *data, int block_id);
t_return_status	duplicate_fds(t_cmd block, t_data *data, char ***env_pt);

void			replace_space_by_minus(unsigned int nb, char *content);

/*-- parsing -----------------------------------------------------------------*/

/*-- clean_utils --*/
void			clean_files_token(t_string_token *lst_of_tok);
void			clean_token(t_string_token *lst_of_tok);

/*-- heredoc_manage --*/

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

/*-- lstc_utils --*/

/*-- path_utils --*/
int				get_path_size(char **paths);
char			**get_paths(char **env);
bool			is_path(char *line);
bool			is_cmd(char *line);

/*-- struct_utils --*/
void			free_commands(t_data *data);

void	execution(t_data *data, t_string_token *lst_of_tok, char ***env_pt);

/*----------------------------------------------------------------------------*/
/*---- Initialisation --------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- env_init--*/

/*----------------------------------------------------------------------------*/
/*---- Lexing_Parsing --------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- 1_preservation ----------------------------------------------------------*/

/*-- double_quoting --*/
/*-- escaping_char --*/
/*-- preserv --*/
/*-- simple_quoting --*/

/*-- 2_metachar_managing -----------------------------------------------------*/

/*-- split_on_meta --*/
/*-- split_toklst_on_meta --*/

/*-- 3_expand_in_parsing -----------------------------------------------------*/

/*-- expand_variable --*/

/*-- 5_suppress_quotes -------------------------------------------------------*/

/*-- suppress_quotes --*/

/*-- parsing_token_utils -----------------------------------------------------*/

/*-- simple_token_utils --*/
/*-- testing_utils --*/
/*-- token_lest_utils_2 --*/
/*-- token_lst_utils --*/

/*-- char_par_err --*/
/*-- check_unic_syntax --*/
/*-- parsing articulation --*/
/*-- syntax_is_valid --*/


/*----------------------------------------------------------------------------*/
/*---- Parsing ---------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- cut_all_lines --*/
/*-- cut_line --*/
/*-- expands --*/
/*-- join_expands --*/
/*-- replace_dollar_str_by_env_value --*/
/*-- replace_dquotes_str_by_env_value --*/


/*----------------------------------------------------------------------------*/
/*---- Signals ---------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- signals --*/
void			init_signals(void);
void			handle_signal_heredoc(int signal);
void			handle_signal_child(int signal);
void			handle_signal_father_process(int signal);

/*----------------------------------------------------------------------------*/
/*---- T_String_Token_Utils --------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- str_token_utils --*/
/*-- t_string_token_utils --*/
/*-- token_to_str_token --*/

/*----------------------------------------------------------------------------*/
/*---- Token_Lst -------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- token_lst_constructor --*/

/*----------------------------------------------------------------------------*/
/*---- Main ------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*-- main_utils --*/
t_return_status	check_arguments(int ac, char **av);
void			clean_the_prompt(char *prompt, char *line, char **env);

/*-- Genius Brieuc utils --*/
void			string_token_destructor(t_string_token *trash);
void			del_next_string_token(t_string_token *tok);
char			**join_token_lst(t_string_token **arg, char **env);
void			manage_ambiguous(t_cmd *cmd, char *file);
t_return_status	expand_for_args(t_string_token *token_lst, char **env);

void			ft_free_all_str_lst(t_data *data, int index);
t_return_status	read_fd_in_str(int fd, char **dst);
t_return_status	heredoc_child_management(t_cmd *cmd, \
						t_data *data, char **env_pt);



/* changer les dossiers? 
-Main
	- utils
	- prompt
- Utils
	- lst_utils
	- debug ?
- Lexing
	- preserv
	- meta_char
	- expand
	- delete
- Parsing
	- articulation
	- expand
	- cut_lines
	- join_expand
	- env_manage
- Syntax
	- check_mistakes
	- check_unic_cases
	- syntax_is_valid
- Init_Env
	- initialise_env
- Execution
	- fetch_arguments
	- manage_arguments
	- utils
	- manage_pipes
	- manage_fds
	- execve
	- cleaning
- Bultins
	- good as it is
- Bonus
	- wildcards
	- parenthesis
	- && ||

*/
#endif