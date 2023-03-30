#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

t_return_status	env_builtin(char **av, char ***env_pt)
{
	char **pin;

	ft_free_split(av);
	pin = *env_pt;
	while (*pin)
	{
		printf("%s\n", *pin);
		pin++;
	}
	return (SUCCESS);
}


#ifdef TST_ENV

int	main(int ac, char **av, char **env)
{
	(void)ac; (void)av; (void)env;

	env = ft_str_array_dup(env);
	av = ft_str_array_dup(av);
	env_builtin(av, &env);
	ft_free_split(env);
	return (0);
}

#endif