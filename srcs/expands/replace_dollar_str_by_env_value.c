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
			&& ft_strchr(new, '='))
		{
			free(*pin_pt);
			*pin_pt = ft_strdup(ft_strchr(new, '=') + 1);
			if (*pin_pt == NULL)
				return (MLC_ERR);
			return (SUCCESS);
		}
		pin_env++;
	}
	*pin_pt = ft_strdup("");
	if (*pin_pt == NULL)
		return (MLC_ERR);
	return (SUCCESS);
}
