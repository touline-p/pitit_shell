/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:53:30 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/22 16:41:23 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NORMAL
#ifdef NORMAL

#include "minishell_parsing.h"

#include "fcntl.h"
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	
	ft_printf(PURPLE"Bonjour Genies Bpoumeau et Twang\n"END);
	// char			*line;
	// t_str_token_lst	*token_lst;
	
	// while (MINI_SHELL_MUST_GO_ON)
	// {
	// 	rl_signal_reset();
	// 	line = readline(PURPLE"prompt : >"END);
	// 	token_lst = lexing_line_to_token_lst(line, env);
	// 	execute_token_lst(token_lst);
	// }
	return (0);
}

#endif