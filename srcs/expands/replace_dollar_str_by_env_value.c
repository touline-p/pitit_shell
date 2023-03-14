#include "../../libft/libft.h"

t_ret_status	replace_dollar_str_by_env_value(char **pin_pt, char **env)
{
	char	**pin_env;
	char	*join;

	pin_env = env;
	join = ft_strjoin(*pin_pt + 1, "=");
	if (!join)
		return (MLC_ERR);
	while (*pin_env)
	{
		if (ft_strncmp(join, *pin_env, ft_strlen(join)) == 0)
		{
			free(*pin_pt);
			*pin_pt = ft_strdup(ft_strchr(*pin_env, '=') + 1);
			free(join);
			if (*pin_pt == NULL)
				return (MLC_ERR);
			return (SUCCESS);
		}
		pin_env++;
	}
	free(*pin_pt);
	free(join);
	*pin_pt = ft_strdup("");
	if (*pin_pt == NULL)
		return (MLC_ERR);
	return (SUCCESS);
}

#ifdef TEST_REPLACE_VAR

int main(int ac, char **av, char **env)
{
	(void )ac; (void)av;
	char *a = ft_strdup("$USER");
	char *b = ft_strdup("$bonjour");
	char *c = ft_strdup("$AHBAH");
	if (replace_dollar_str_by_env_value(&a, env) == SUCCESS)
		printf("a :->%s<-\n", a);
	if (replace_dollar_str_by_env_value(&b, env) == SUCCESS)
		printf("b :->%s<-\n", b);
	if (replace_dollar_str_by_env_value(&c, env) == SUCCESS)
		printf("c :->%s<-\n", c);
	free(a);
	free(b);
	free(c);
}

#endif