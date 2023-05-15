/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:58:54 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/03 18:20:47 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static	t_return_status	_unset_builtin_ep(char *msg, char **trash, \
							t_return_status ret_val);

t_return_status	unset_builtin(char **args, char ***env_pt)
{
	char	**tmp;
	char	*line_to_del;

	if (ft_str_array_len(args) == 1)
		return (_unset_builtin_ep("", \
				args, SUCCESS));
	tmp = args + 1;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '=') != NULL)
		{
			tmp++;
			continue ;
		}
		line_to_del = get_line_from_key(*tmp, *env_pt);
		if (line_to_del != NULL)
			if (del_str_from_env(line_to_del, env_pt))
				return (_unset_builtin_ep("unset: malloc_failed\n", \
				args, FAILED_MALLOC));
		tmp++;
	}
	g_ret_val = 0;
	ft_free_split(args);
	return (SUCCESS);
}

static	t_return_status	_unset_builtin_ep(char *msg, char **trash, \
							t_return_status ret_val)
{
	if (trash != NULL)
		ft_free_split(trash);
	dprintf(2, "%s", msg);
	g_ret_val = 1;
	return (ret_val);
}
