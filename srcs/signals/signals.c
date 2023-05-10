/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:50:13 by twang             #+#    #+#             */
/*   Updated: 2023/05/09 21:04:30 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	handle_signal_main(int signal);

/*----------------------------------------------------------------------------*/

void	init_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, &handle_signal_main);
}

static void	handle_signal_main(int signal)
{
	(void)signal;
	g_ret_val = 130;
	ft_dprintf(2, GREEN"\tPLEASE DON'T STOP THE MUSIC\n"END);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		ft_dprintf(2, "\n");
		g_ret_val = 130;
		exit (g_ret_val);
	}
	else if (signal == SIGQUIT)
		(void)signal;
}

void	handle_signal_child(int signo)
{
	if (signo == SIGINT)
	{
		g_ret_val = 130;
		ft_dprintf(2, "\n");
	}
	else if (signo == SIGQUIT)
	{
		g_ret_val = 131;
		ft_dprintf(2, RED"Quit (core dumped)\n"END);
	}
}

void	handle_signal_father_process(int signal)
{
	(void)signal;
	g_ret_val = 130;
}
