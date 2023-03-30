#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

t_return_status	cd_builtin(char **av, char ***env_pt)
{
	(void)env_pt;
	if (ft_str_array_len(av) != 2)
		return (dprintf(2, "cd: bad arguments number\n"), ft_free_split(av), SUCCESS);
//	if (ft_str_array_len(av) == 1)
//		return (_go_to_home(env_pt));

	chdir(av[1]);
	if (errno)
	{
		perror(av[1]);
		return (FAILURE);
	}
	return (SUCCESS);
}

#ifdef CD_TST
int main(int ac, char **av, char **env)
{
	(void)ac; (void)av; (void)env;

	env = ft_str_array_dup(env);
	av = ft_str_array_dup(av);
	puts(getcwd(NULL, 0));
	cd_builtin(av, &env);
	puts(getcwd(NULL, 0));
	ft_free_split(env);
	return (0);
}
#endif