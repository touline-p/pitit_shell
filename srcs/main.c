/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:53:30 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/21 13:58:52 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifdef NORMAL

#include "minishell.h"

#include "fcntl.h"
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_str_token_lst	*token_lst;

	while (MINI_SHELL_MUST_GO_ON)
	{
		rl_signal_reset();
		line = readline("prompt : >");
		token_lst = lexing_line_to_token_lst(line, env);
		execute_token_lst(token_lst);
	}
	return (0);
}

#endif