/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:25:03 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 16:12:35 by twang            ###   ########.fr       */
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