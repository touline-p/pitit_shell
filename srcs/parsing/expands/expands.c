#include "minishell_parsing.h"

t_ret_status	performe_expand_on_line(char **line_pt, char **env)
{
	char **line_arr;
	char **pin;

	if (cut_line_on(*line_pt, &line_arr) != success)
		return ();
	printf("i m here\n");
	pin = line_arr;
	while (pin && *pin)
	{
		if (**pin == '$' && \
		replace_dollar_str_by_env_value(pin, env) != success)
			return (failed_malloc);
		pin++;
	}
	if (ft_join_str_arr_on(line_arr, line_pt) != success)
		return (ft_free_split(line_arr), failed_malloc);
	ft_free_split(line_arr);
	return (success);
}

#define TST_EXPAND
#ifdef TST_EXPAND

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	char *line = ft_strdup("expand qui marche $USERU $test");
	printf("origine:\n->%s<-\n", line);
	if (performe_expand_on_line(&line, env) != success)
		return (perror("allocation"), 1);
	printf("test:\n->%s<-\n", line);
	free(line);
	printf("I am so smart!\n");
	return (0);
}

#endif
