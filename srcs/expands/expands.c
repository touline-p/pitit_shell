#include "cut_line.h"

#define TST_EXPAND

t_ret_status	performe_expand_on_line(char **line_pt, char **env)
{
	char **line_arr;
	char *pin;

	if (cut_line_on(*line_pt, &line_arr) != SUCCESS)
		return (MLC_ERR);
	pin = *line_arr;
	while (pin)
	{
		if (*pin == '$' && replace_dollar_str_by_env_value(&pin, env) != SUCCESS)
			return (MLC_ERR);
		pin++;
	}
	if (ft_join_str_arr_on(line_arr, line_pt) != SUCCESS)
		return (MLC_ERR);
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
