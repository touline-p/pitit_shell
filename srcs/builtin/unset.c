#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static	t_return_status	_unset_builtin_ep(char *msg, t_return_status ret_val);

t_return_status	unset_builtin(char **args, char ***env_pt)
{
	char **tmp;
	char *line_to_del;

	if (ft_str_array_len(args) == 1)
		return (_unset_builtin_ep("unset: not enough arguments", SUCCESS);
	tmp = args + 1;
	while (*tmp)
	{
		line_to_del = get_line_from_key(*tmp, *env_pt);
		if (line_to_del != NULL)
			del_str_from_env(line_to_del, env_pt);
		tmp++;
	}
	return (SUCCESS);
}
