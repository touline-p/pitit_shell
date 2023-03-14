#include "../../libft/libft.h"

t_ret_status	replace_dollar_str_by_env_value(char **pin_pt, char **env)
{
	char	**pin_env;
	char	*new;

	pin_env = env;
	new = *pin_pt + 1;
	while (*pin_env)
	{
		if (ft_strncmp(new, *pin_env, ft_strlen(new)) == 0
			&& ft_strchr(*pin_env, '='))
		{
			free(*pin_pt);
			*pin_pt = ft_strdup(ft_strchr(*pin_env, '=') + 1);
			if (*pin_pt == NULL)
				return (MLC_ERR);
			return (SUCCESS);
		}
		pin_env++;
	}
	free(*pin_pt);
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
	replace_dollar_str_by_env_value(&a, env);
	replace_dollar_str_by_env_value(&b, env);
	replace_dollar_str_by_env_value(&c, env);
	printf("a :->%s<-\n", a);
	printf("b :->%s<-\n", b);
	printf("c :->%s<-\n", c);
}

#endif