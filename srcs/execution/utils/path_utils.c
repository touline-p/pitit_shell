/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:50:36 by twang             #+#    #+#             */
/*   Updated: 2023/04/13 18:16:36 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static int	find_path_in_environment(char **env);

/*----------------------------------------------------------------------------*/

int	get_path_size(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	return (i);
}

char	**get_paths(char **env)
{
	int		i;
	int		find_path;
	char	**paths;

	find_path = find_path_in_environment(env);
	if (find_path == -1)
		return (NULL);
	paths = ft_split(&env[find_path][5], ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = strjoin_path_cmd(paths[i], "/");
		if (!paths[i])
		{
			ft_free((void **)paths, get_path_size(paths));
			return (NULL);
		}
		i++;
	}
	return (paths);
}

static int	find_path_in_environment(char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (FAILURE);
	return (i);
}
