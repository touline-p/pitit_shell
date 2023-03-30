#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

t_return_status	pwd_builtin(char **args, char ***env_pt)
{
	char *pwd;

	(void)env_pt;
	if (ft_str_array_len(args) > 1)
		return (dprintf(2, "pwd: too many arguments\n"), ft_free_split(args), FAILURE);
	ft_free_split(args);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (dprintf(2, "Bro j'ai pas trouve dsl, tu es perdu :(\n"), FAILURE);
	printf("%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}

#ifdef TST_PWD

int	main(int ac, char **av, char **env)
{
	av = ft_str_array_dup(av);
	env = ft_str_array_dup(env);
	pwd_builtin(av, &env);
	ft_free_split(env);
	return (0);
}

#endif