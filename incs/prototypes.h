/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:25:03 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 16:24:10 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/*---- includes --------------------------------------------------------------*/

# include "structures.h"

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*---- Main ------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*---- prompt ----------------------------------------------------------------*/
/*---- prompt.c ----*/
t_return_status	get_prompt_on(char **prompt_pt, char **env);

/*---- prompt_utils.c ----*/
void			copy_all_box(char *box, char *pwd, size_t box_width);
t_return_status	clean_the_prompt(char *prompt, char *line, char **env);

/*---- utils -----------------------------------------------------------------*/
/*---- display.c ----*/
t_return_status	welcome_to_minihell(char ***env_pt);

/*---- utils.c ----*/
t_return_status reset_term_settings(t_data *data);
t_return_status	init_main(t_data *data, t_string_token **str_token_pt, \
				char **av, char ***env_pt);
void			loop_init(t_data *data, char **line_pt, char **env);
t_return_status set_data_instruction_arr(t_data *data, t_string_token *str_tok_lst);
int				go_fuck_yourself_malloc(t_string_token *token_lst, char **env);

/*----------------------------------------------------------------------------*/
/*---- Signals ---------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*---- signals_utils.c ----*/
char		*update_prompt(char *prompt);
const char	get_color(void);

/*---- signals.c ----*/
void		init_signals(t_data *data);
void		handle_signal_heredoc(int signal);
void		handle_signal_child(int signo);
void		handle_signal_father_process(int signal);



#endif