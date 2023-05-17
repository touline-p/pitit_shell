/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:25:03 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 14:07:34 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/*---- includes --------------------------------------------------------------*/

# include "structures.h"

/*----------------------------------------------------------------------------*/

t_return_status	cut_line_on(char *line, char ***res_pt);
t_return_status	performe_expand_on_line(char **line_pt, char **env);
t_return_status	replace_dollar_str_by_env_value(char **pin_pt, char **env);

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

t_return_status	is_control_operator(t_emt token);

t_return_status	escaping_chars(t_token *tok);
t_return_status	escape_process(t_token *last_pt, \
								t_token *tok, t_token **voided);
t_return_status	dquoting_process(t_token *voided, \
								t_token *last_token, \
								t_token **end_of_quot_pt);
t_return_status	squoting_process(t_token *voided, \
								t_token *token, t_token **end_of_quot_pt);

t_token			*split_toklst_on_meta(t_token *tok);
t_token			*regroup_meta(t_token *tok);
t_token			*split_on_meta(t_token *tok);

t_return_status	expand_dollars(t_token *token_lst, char **env);
void			suppress_quotes(t_token *tok);
t_token			*get_next_emt(t_token *tok);

t_string_token	*string_token_creator(void);
t_return_status	string_token_creator_on(t_string_token **tok_pt);
t_string_token	*token_lst_to_str_token(t_token *tok);
void			string_token_destructor(t_string_token *trash);
void			cpy_token_lst_to_str(t_token *tok, char *str);
int				next_control_operator_is_a_pipe(t_string_token *tok);
void			del_next_string_token(t_string_token *tok);
void			del_space_token(t_string_token *tok);
t_return_status	split_t_string_token_on_space(t_string_token **token_pt);
void			del_empty_tokens(t_string_token *token_lst);
void			free_all_str(t_data *data);

t_return_status	syntax_is_valid(t_string_token *lst_to_check);

t_return_status	env_init_on(char ***env_pt);
char			*get_line_from_key(char *key, char **env);
bool			is_a_key_from_env(char *key, char **env);
char			*get_env_content_from_key(char *key, char **env);
t_return_status	add_str_to_env(char *line, char ***env_pt);
t_return_status	del_str_from_env(char *line, char ***env_pt);
void			display_str_par(t_string_token *tok);
size_t			go_to_next_(t_emt token, t_string_token *tmp, \
								t_string_token **str_tok);

char			*get_first_line_in_env(char **env);
char			*get_next_line_in_env(char *last, char **env);
char			**get_line_addr_from_key(char *key, char **env);
void			replace_content_in_env(char *line, char **env);
bool			has_a_key_from_env(char *line, char **env);

t_return_status	expand_for_args(t_string_token *token_lst, char **env);

t_return_status	cut_all_lines(t_string_token *string_token_lst);
t_return_status	join_all_lines(t_string_token *string_token_lst, char **env);
t_return_status	join_arr_on(char **str_arr, char **line_pt, char **env);

void			per_n_set_errno(char *msg);
bool			file_is_empty(char *file);

void			display_tokens(t_token *token_lst);
void			display_t_emt(t_token *token);
void			put_esec(t_token *tok);
void			display_str_token(t_string_token *tok);
void			display_str_token_till(t_string_token *tok);
char			*_get_env_variable(t_token *token, char **env);
void			cpy_next_char(unsigned int index, char *str);
t_return_status	replace_dquotes_str_by_env_value(char **line_pt, char **env);
t_return_status	get_lexed_str_token_lst_from_line(char *line, \
						t_string_token **str_tok_pt, char **env);

void			update_tokens(t_string_token *str_tok_lst);
bool			is_a_redir(t_emt token);

void			go_to_next_logical_door(t_string_token *src, \
											t_string_token **dst);
char			*format_string_token(t_string_token *token);
void			check_par_err(t_string_token *str_tok_lst);

t_return_status	check_line(char *line);
int				get_alloc_size(char *line);
t_return_status	find_matching_files(char *line, char *name);
void			replace_wild_card(char *line);
t_return_status	wildcard_files(t_data *data, char **file, int block_id);
t_return_status	fill_dst_arr(char *line, char **arr_to_fill);

t_return_status	expand_wildcards(char ***original_pt);

void			execution(t_data *data, t_string_token *lst_of_tok, \
							char ***env_pt);

void			replace_space_by_minus(unsigned int nb, char *content);

t_return_status	childs_execve(t_data *data, char ***env);

t_return_status	heredoc_management(t_data *data, t_string_token *str_tok_lst, \
									char **env);
t_return_status	check_unic_syntax(t_string_token *actual, bool *string, \
									t_pr_stat *in_parentheses);
void			close_fds(t_data *data, int block_id);
void			close_all_fds(t_data *data, int block_id);
t_return_status	duplicate_fds(t_cmd block, t_data *data, char ***env_pt);

void			clean_files_token(t_string_token *lst_of_tok);
void			clean_token(t_string_token *lst_of_tok);

t_return_status	files_management(t_data *data, t_string_token *lst_of_tok, \
						char **env);

t_return_status	outfiles_management(t_data *data, t_string_token *lst_of_tok, \
						char **env);

void			strings_management(t_data *data, t_string_token *lst_of_tok, \
						char **env_pt);

t_builtin		is_builtin(char *string);
t_return_status	builtin_switch(t_cmd command, char **av, char ***env_pt);

void			check_opened_infiles(t_data *data, int block_id);
void			check_opened_outfiles(t_data *data, int block_id);
t_return_status	redirection_syntax_error(char *str);
bool			redir_failed(t_cmd *cmd);

int				get_path_size(char **paths);
char			**get_paths(char **env);
bool			is_path(char *line);
bool			is_cmd(char *line);

void			free_commands(t_data *data);

void			init_signals(t_data *data);
void			handle_signal_child(int signal);
void			handle_signal_heredoc(int signal);
void			handle_signal_heredoc_sigquit(int signal);
void			handle_signal_father_process(int signal);

void			string_token_destructor(t_string_token *trash);
void			del_next_string_token(t_string_token *tok);
void			display_str_token(t_string_token *tok);
void			display_t_emt_string(t_string_token *token);
char			**join_token_lst(t_string_token **arg, char **env);
t_return_status	join_token_lst_on(t_cmd *cmd, t_string_token **arg, char **env);
void			manage_ambiguous(t_cmd *cmd, char *file);
t_return_status	expand_for_args(t_string_token *token_lst, char **env);
t_return_status	switchman(t_data *data, \
						t_string_token *token_lst, char ***env_pt);
void			ft_free_all_str_lst(t_data *data, int index);
t_return_status	read_fd_in_str(int fd, char **dst);
t_return_status	heredoc_child_management(t_cmd *cmd, \
						t_data *data, char **env_pt);
char			**subshell_preparation(t_string_token **start);

t_return_status	check_arguments(char **av);
t_return_status	clean_the_prompt(char *prompt, char *line, char **env);

t_return_status	get_prompt_on(char **prompt_pt, char **env);
char			*get_prompt(char *str, int flag);

void			print_pid(int pid);
void			print_fd(char *msg, int fd);
void			print_is_heredoc(bool is);
void			print_builtin(t_builtin built);
void			print_cmd_block(char *msg, t_cmd cmd);

t_return_status	switchman_once(t_data *data, char ***env_pt);
t_return_status	cd_builtin(char **av, char ***env_pt);
t_return_status	export_builtin(char **av, char ***env_pt);
t_return_status	env_builtin(char **av, char ***env_pt);
t_return_status	pwd_builtin(char **av, char ***env_pt);
t_return_status	unset_builtin(char **av, char ***env_pt);
t_return_status	echo_builtin(char **av, char ***env_pt);
t_return_status	exit_builtin(char **av, char ***env_pt);

#endif