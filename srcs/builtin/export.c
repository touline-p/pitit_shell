/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:58:27 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/04/26 22:58:28 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static t_return_status	_export_display(char **env);
static void				_display_unic_export(char *env_line);
static t_export_ft		get_ft_to_do(char *line, char **env);

t_return_status	export_builtin(char **args, char ***env_pt)
{
	char		**tmp;

	if (ft_str_array_len(args) == 1)
		return (ft_free_split(args), _export_display(*env_pt), SUCCESS);
	tmp = args + 1;
	while (*tmp != NULL)
	{
		if ((*get_ft_to_do(*tmp, *env_pt))(*tmp, env_pt) != SUCCESS)
			return (free(*args), ft_free_split(tmp), FAILED_MALLOC);
		tmp++;
	}
	return (free(*args), free(args), SUCCESS);
}

void	_get_rid_of_plus(char *line)
{
	if (line == NULL)
		return ;
	while (*line != '=' && *line)
	{
		if (*line == '+')
		{
			ft_memmove(line, line + 1, ft_strlen(line));
			return ;
		}
		line++;
	}
}

t_return_status	replace_content_in_env_pt(char *line, char ***env_pt)
{
	return (replace_content_in_env(line, *env_pt), SUCCESS);
}

t_return_status	do_nothing_t_export_ft(char *line, char ***env_pt)
{
	(void)line;
	(void)env_pt;
	return (SUCCESS);
}

t_return_status	concat_content_to_line_in_env(char *line, char ***env_pt)
{
	char	*content;
	char	**env_line;
	char	*tmp;

	content = ft_strchr(line, '=');
	*(content++) = 0;
	env_line = get_line_addr_from_key(line, *env_pt);
	tmp = *env_line;
	*env_line = ft_strjoin(*env_line, content);
	free(tmp);
	free(line);
	return (SUCCESS);
}

bool	key_is_not_alnum(char *line)
{
	while (*line != '=' && *line)
	{
		if (*line == '+' && *(line + 1) == '=')
			return (false);
		if (ft_isalnum(*line) == false)
			return (true);
		line++;
	}
	return (false);
}

t_return_status	not_in_context_error(char *line, char ***env_pt)
{
	(void)env_pt;
	if (dprintf(2, "export : '%s': not a valid identifier\n", line) == -1)
		return (free(line), FAILED_WRITE);
	return (free(line), SUCCESS);
}

static t_export_ft	get_ft_to_do(char *line, char **env)
{
	char	*eq;
	char	*plus;

	eq = ft_strchr(line, '=');
	plus = ft_strchr(line, '+');
	_get_rid_of_plus(line);
	if (key_is_not_alnum(line))
		return (&not_in_context_error);
	if (has_a_key_from_env(line, env) == false)
		return (&add_str_to_env);
	if (eq == NULL)
		return (&do_nothing_t_export_ft);
	if (plus == eq - 1)
		return (&concat_content_to_line_in_env);
	return (&replace_content_in_env_pt);
}

static t_return_status	_export_display(char **env)
{
	char	*line;

	line = get_first_line_in_env(env);
	while (line != NULL )
	{
		if (!(line[0] == '_' && line[1] == '='))
			_display_unic_export(line);
		line = get_next_line_in_env(line, env);
	}
	return (SUCCESS);
}

static void	_display_unic_export(char *env_line)
{
	char	*content;

	content = ft_strchr(env_line, '=');
	if (content == NULL)
	{
		printf("declare -x %s\n", env_line);
		return ;
	}
	*(content++) = 0;
	printf("declare -x %s=\"%s\"\n", env_line, content);
	*(--content) = '=';
}
