#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static	bool	_is_option_n(char *arg);

t_return_status	echo_builtin(char **av, char ***env_pt)
{
	char **tmp;
	bool option;

	(void)env_pt;
	tmp = av + 1;
	option = _is_option_n(*tmp);
	if (option == true)
		tmp++;
	if (*tmp)
	{
		printf("%s", *tmp);
		tmp++;
	}
	while (*tmp)
	{
		printf(" %s", *tmp);
		tmp++;
	}
	if (option == false)
		printf("\n");
	return (SUCCESS);
}

static	bool	_is_option_n(char *arg)
{
	if (arg == NULL || *(arg) != '-' || *(arg + 1) != 'n')
		return (false);
	arg++;
	while (*arg == 'n')
		arg++;
	if (*arg)
		return (false);

	return (true);
}


#ifdef TST_ECHO

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
