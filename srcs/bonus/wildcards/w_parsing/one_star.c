/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_star.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:41:19 by twang             #+#    #+#             */
/*   Updated: 2023/05/10 13:29:54 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_only_star(char *name);
static t_return_status	_star_start(char *line, char *name);
static t_return_status	_star_end(char *line, char *name);
static t_return_status	_star_middle(char *line, char *name);

/*----------------------------------------------------------------------------*/

t_return_status	one_star_case(t_w_data *w_data, char *line, char *name)
{
	if (strcmp(line, "*") == 0)
	{
		if (_only_star(name) != FAILURE)
			return (SUCCESS);
	}
	else if (w_data->first == '*')
	{
		if (_star_start(line, name) != FAILURE)
			return (SUCCESS);
	}
	else if (w_data->last == '*')
	{
		if (_star_end(line, name) != FAILURE)
			return (SUCCESS);
	}
	else
	{
		if (_star_middle(line, name) != FAILURE)
			return (SUCCESS);
	}
	return (FAILURE);
}

static t_return_status	_only_star(char *name)
{
	if (name[0] != '.')
	{
		printf("%s\n", name);
		return (SUCCESS);
	}
	return (FAILURE);
}

static t_return_status	_star_start(char *line, char *name)
{
	int	line_len;

	line_len = 0;
	line++;
	line_len = ft_strlen(line);
	if (ft_strncmp(name + ft_strlen(name) - line_len, line, line_len) == 0)
	{
		printf("%s\n", name);
		return (SUCCESS);
	}
	return (FAILURE);
}

static t_return_status	_star_end(char *line, char *name)
{
	int	line_len;

	line_len = 0;
	line_len = ft_strlen(line) - 1;
	if (ft_strncmp(name, line, line_len) == 0)
	{
		printf("%s\n", name);
		return (SUCCESS);
	}
	return (FAILURE);
}

static t_return_status	_star_middle(char *line, char *name)
{
	(void)name;
	char	**splited_line;

	splited_line = NULL;
	splited_line = ft_split(line, '*');
	// printf(GREEN"%s\n"END, splited_line[0]);
	// printf(RED"%s\n"END, splited_line[1]);
	if (ft_strncmp(name, splited_line[0], ft_strlen(splited_line[0])) == 0 && ft_strncmp(name + ft_strlen(name) - ft_strlen(splited_line[1]), splited_line[1], ft_strlen(splited_line[1])) == 0)
	{
		printf("%s\n", name);
		return (SUCCESS);
	}
	free(splited_line);
	return (FAILURE);
}
