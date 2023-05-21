/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:50:13 by twang             #+#    #+#             */
/*   Updated: 2023/05/19 15:37:21 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---- prototypes ------------------------------------------------------------*/

static void	handle_signal_main(int signal);

/*----------------------------------------------------------------------------*/

void	init_signals(t_data *data)
{
	if (tcgetattr(1, &data->term) == -1)
	{
		perror("tcgetattr");
		errno = SUCCESS;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, &handle_signal_main);
}

static void	handle_signal_main(int sign)
{
	char	*prompt;

	(void)sign;
	g_ret_val = 130;
	ft_dprintf(2, GREEN"\tPLEASE DON'T STOP THE MUSIC\n"END);
	prompt = get_prompt(NULL, 0);
	prompt = update_prompt(prompt);
	printf("%s", prompt);
	//rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		ft_dprintf(2, "^C");
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
