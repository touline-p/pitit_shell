/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:50:13 by twang             #+#    #+#             */
/*   Updated: 2023/04/24 17:32:23 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"


void	handle_signal_main(int signal)
{
	(void)signal;
	dprintf(2, GREEN"\tPLEASE DON'T STOP THE MUSIC\n"END);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_ret_val = 1;
}

void	handle_signal_child(int signal)
{
	(void)signal;
	dprintf(2, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handle_signal_heredoc(int signal)
{
	(void)signal;
	dprintf(2, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_ret_val = 1;
	exit (g_ret_val);
}

void	handle_signal_heredoc_sigquit(int signal)
{
	(void)signal;
}
