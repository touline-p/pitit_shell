#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"



#ifdef TST_ENV

int	main(int ac, char **av, char **env)
{
	(void)ac; (void)av; (void)env;

	env = ft_str_array_dup(env);
	av = ft_str_array_dup(av);
	echo_builtin(av, &env);
	ft_free_split(env);
	return (0);
}

#endif
