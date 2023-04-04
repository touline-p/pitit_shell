/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:41:03 by twang             #+#    #+#             */
/*   Updated: 2023/03/27 17:44:46 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

/*---- prototypes ------------------------------------------------------------*/

static int	get_path_size(char **paths);
static int	find_path_in_environment(char **env);
static char	**get_paths(char **env);

/*----------------------------------------------------------------------------*/
char	*get_command_with_path(char **env, char *command)
{
	int		i;
	char	**paths;
	char	*valid_path;

	if (access(command, X_OK) == 0)
		return (command);
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], command);
		if (!paths[i])
			return (ft_free((void **)paths, get_path_size(paths)));
		if (access(paths[i], X_OK) == 0)
		{
			valid_path = ft_strdup(paths[i]);
			ft_free((void **)paths, get_path_size(paths));
			return (valid_path);
		}
		i++;
	}
	ft_dprintf(2, "command not found: %s\n", command);
	return (NULL);
}

static int	get_path_size(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	return (i);
}

static int	find_path_in_environment(char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (-1);
	return (i);
}

static char	**get_paths(char **env)
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
		paths[i] = ft_strjoin(paths[i], "/");
		if (!paths[i])
		{
			ft_free((void **)paths, get_path_size(paths));
			return (NULL);
		}
		i++;
	}
	return (paths);
}
