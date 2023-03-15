//
// Created by bpoumeau on 3/14/23.
//


#ifdef NORMAL

#include "main.h"

#include "fcntl.h"
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_str_token_lst	*token_lst;

	while (MINI_SHELL_MUST_GO)
	{
		line = readline("prompt : >");
		token_lst = lexing_line_to_token_lst(line, env);
		execute_token_lst(token_lst, env);
	}
	return (0);
}

#endif