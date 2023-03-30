#include "../../../libft/libft.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

char *get_first_line_in_env(char **env)
{
	char *ret_val;

	ret_val = *(env++);
	while (*env != NULL) {
		if (ft_strcmp(ret_val, *env) > 0)
			ret_val = *env;
		env++;
	}
	return (ret_val);
}

char *get_next_line_in_env(char *last, char **env)
{
	char *line;
	line = NULL;
	while (*env)
	{
		if (ft_strcmp(last, *env) < 0 \
			&& (line == NULL || ft_strcmp(*env, line) < 0))
			line = *env;
		env++;
	}
	return (line);
}