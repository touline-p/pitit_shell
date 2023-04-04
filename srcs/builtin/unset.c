#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static	t_return_status	_unset_builtin_ep(char *msg, char **trash, t_return_status ret_val);

t_return_status	unset_builtin(char **args, char ***env_pt)
{
	char **tmp;
	char *line_to_del;

	if (ft_str_array_len(args) == 1)
		return (_unset_builtin_ep("unset: not enough arguments", args, SUCCESS));
	tmp = args + 1;
	while (*tmp)
	{
		line_to_del = get_line_from_key(*tmp, *env_pt);
		if (line_to_del != NULL)
			if (del_str_from_env(line_to_del, env_pt))
				return (_unset_builtin_ep("unset: malloc_failed", args, FAILED_MALLOC));
		tmp++;
	}
	ft_free_split(args);
	return (SUCCESS);
}

static	t_return_status	_unset_builtin_ep(char *msg, char **trash, t_return_status ret_val)
{
	if (trash != NULL)
		ft_free_split(trash);
	dprintf(2, "%s\n", msg);
	return (ret_val);
}

#ifdef TST_UNSET

int	main(int ac, char **av, char **env)
{
	(void)ac; (void)av; (void)env;

	env = ft_str_array_dup(env);
	av = ft_str_array_dup(av);
	unset_builtin(av, &env);
	ft_print_split(env);
	ft_free_split(env);
	return (0);
}

#endif