/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:50:13 by twang             #+#    #+#             */
/*   Updated: 2023/05/03 11:46:32 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static void	disable_signal_display(void);
static void	handle_signal_main(int signal);

/*----------------------------------------------------------------------------*/

void	init_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	disable_signal_display();
	signal(SIGINT, &handle_signal_main);
}

static void	disable_signal_display(void)
{
	struct termios attribute;
    tcgetattr(STDIN_FILENO, &attribute);
    attribute.c_lflag &= ~ISIG;
    tcsetattr(STDIN_FILENO, TCSANOW, &attribute);
}

static void	handle_signal_main(int signal)
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
	if (signal == SIGINT)
	{
		ft_dprintf(2, "\n");
		g_ret_val = 130;
	}
	else if (signal == SIGQUIT)
	{
		ft_dprintf(2, "\n");
		ft_dprintf(2, RED"minishell: Quit (core dumped)\n"END);
		g_ret_val = 131;
	}
}

void	handle_signal_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		ft_dprintf(2, "\n");
		g_ret_val = 1;
		exit (g_ret_val);
	}
	else if (signal == SIGQUIT)
	{
		(void)signal;
	}
}

/*
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
	// g_ret_val = 130;
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
*/