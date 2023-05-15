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

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"
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

char 	*get_color( void )
{
	if (g_ret_val == 130)
		return (YELLOW);
	else
		return (0);
}

void	change_color(char *prompt)
{
	char	*tmp;
	char 	*color;

	color = get_color();
	tmp = ft_strnstr(prompt, GREEN, ft_strlen(prompt));
	while (tmp)
	{
		ft_memcpy(tmp, color, ft_strlen(color));
		tmp = ft_strnstr(prompt, GREEN, ft_strlen(prompt));
	}
}

char	*update_prompt(char *prompt)
{
	char	*end;

	change_color(prompt);
	end = ft_strjoin_free_first_sf(ft_itoa(g_ret_val), " - Y a quoi : ");
	prompt[ft_strchr(prompt + 350, ':') - prompt + 2] = 0;
	end = ft_strjoin_free_sec_sf(prompt, end);
	return (end);
}

static void	handle_signal_main(int signal)
{
	(void)signal;
	char	*prompt;

	g_ret_val = 130;
	ft_dprintf(2, GREEN"\tPLEASE DON'T STOP THE MUSIC\n"END);
	prompt = get_prompt(NULL, 0);
	prompt = update_prompt(prompt);
	printf("%s", prompt);
	//rl_on_new_line();
	rl_replace_line("", 0);
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
