#include "expands.h"

t_ret_status	performe_expand_on_line(char **line_pt, char **env)
{
	char **line_arr;

	(void)line_arr;
	(void)line_pt;
	(void)env;

	return (SUCCESS);
}




#ifdef TST_EXPAND
#include <stdio.h>
int	main(int ac, char **av, char **env)
{
	(void)ac; (void)av;
	char	*line = ft_strdup("expand qui marche $USER, expand qui marche pas ->$USERU<- $test");
	printf("origine:\n->%s<-\n", line);
	performe_expand_on_line(&line, env);
	printf("test:\n->%s<-\n", line);
	free(line);
	return (0);
}
#endif
