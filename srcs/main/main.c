//
// Created by bpoumeau on 3/14/23.
//


#ifdef NORMAL

#include "main.h"

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_str_token_lst	*token_lst;
	(void)ac;
	(void)av;
	(void)env;

		line = readline("prompt : >");
		printf("line = %s\n", line);
		rl_replace_line("replaced line", 0);
		rl_redisplay();
		line = readline("prompt : >");
	return (0);
}

#endif