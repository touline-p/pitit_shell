/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:50:36 by twang             #+#    #+#             */
/*   Updated: 2023/05/19 15:57:16 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---- prototypes ------------------------------------------------------------*/

static int	find_path_in_environment(char **env);
static int	_get_path_size(char **paths);

/*----------------------------------------------------------------------------*/

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
			ft_free((void **)paths, _get_path_size(paths));
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

static int	_get_path_size(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	return (i);
}
