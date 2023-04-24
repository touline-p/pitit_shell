/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:50:13 by twang             #+#    #+#             */
/*   Updated: 2023/04/24 11:45:43 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"


void	handle_signal_main(int signal)
{
	(void)signal;
	dprintf(2, "\n");
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
	g_ret_val = 1;
}

void	handle_signal_heredoc(int signal)
{
	(void)signal;
	dprintf(2, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_ret_val = 1;
}
