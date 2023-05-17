/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:50:13 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 13:45:19 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"
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

const char	*get_color(void)
{
	const char	*color_arr[] = {GREEN, RED, YELLOW, BLUE, RED};
	const int	ret_val_arr[] = {0, 1, 130, 131};
	size_t		index;

	index = 0;
	while (ret_val_arr[index] != g_ret_val && index < 4)
		index++;
	return (color_arr[index]);
}

const char	*get_color_from_prompt(char *prompt)
{
	const char	*color_arr[] = {GREEN, RED, YELLOW, BLUE, RED};
	size_t		index;

	index = 0;
	while (index < 5)
	{
		if (ft_strnstr(prompt, (char *)color_arr[index], ft_strlen(prompt)) != NULL)
			return (color_arr[index]);
		index++;
	}
	return (NULL);
}

void	change_color(char *prompt)
{
	char		*tmp;
	const char	*color_to;
	const char	*color_from;

	color_to = get_color();
	color_from = get_color_from_prompt(prompt);
	if (color_from == NULL)
		return ;
	tmp = ft_strnstr(prompt, color_from, ft_strlen(prompt));
	while (tmp)
	{
		ft_memcpy(tmp, color_to, ft_strlen(color_to));
		tmp = ft_strnstr(prompt, color_from, ft_strlen(prompt));
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
	char	*prompt;

	(void)signal;
	g_ret_val = 130;
	ft_dprintf(2, GREEN"\tPLEASE DON'T STOP THE MUSIC\n"END);
	prompt = get_prompt(NULL, 0);
	prompt = update_prompt(prompt);
	printf("%s", prompt);
	rl_replace_line("", 0);
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
