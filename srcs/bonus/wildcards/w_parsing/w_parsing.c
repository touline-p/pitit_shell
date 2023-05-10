/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:41:19 by twang             #+#    #+#             */
/*   Updated: 2023/05/10 11:49:15 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_check_line(t_w_data *w_data, char *line);
static int				_get_alloc_size(t_w_data *w_data, char *line);
static	t_return_status	_find_matching_files(t_w_data *w_data, char *line, \
											char *name);
/*----------------------------------------------------------------------------*/

t_return_status	parse_args(t_w_data *w_data, char *line)
{
	int	size;

	size = 0;
	if (_check_line(w_data, line) != SUCCESS)
		return (FAILURE);
	size = _get_alloc_size(w_data, line);
	if (size <= 0)
		return (FAILURE);
	w_data->match = ft_calloc(size + 1, sizeof(char *));
	if (!w_data->match)
		return (FAILURE);
	return (SUCCESS);
}

static t_return_status	_check_line(t_w_data *w_data, char *line)
{
	w_data->first = line[0];
	while (*line)
	{
		if (*line == '*')
			w_data->nb_of_stars++;
		if (*line == '/')
		{
			ft_dprintf(2, RED"minishell: /: bonus wildcards can be used only \
			in the current directory\n"END);
			return (FAILURE);
		}
		if (*(line + 1) == '\0')
			w_data->last = *line;
		line++;
	}
	if (w_data->nb_of_stars <= 0)
		return (FAILURE);
	return (SUCCESS);
}

static int	_get_alloc_size(t_w_data *w_data, char *line)
{
	struct dirent	*data;
	DIR				*directory;
	int				size;

	size = 0;
	directory = opendir(".");
	if (!directory)
	{
		perror ("minishell: opendir: cannot open current directory");
		return (-1);
	}
	while (1)
	{
		data = readdir(directory);
		if (data == NULL)
			break ;
		if (_find_matching_files(w_data, line, data->d_name) == SUCCESS)
			size++;
	}
	closedir(directory);
	ft_dprintf(2, GREEN"size alloc :%d\n"END, size);
	return (size);
}

static	t_return_status	_find_matching_files(t_w_data *w_data, char *line, \
											char *name)
{
	if (w_data->nb_of_stars == 1)
	{
		if (one_star_case(w_data, line, name) != FAILURE)
			return (SUCCESS);
	}
	else
	{
		if (multi_stars_case(w_data, line, name) != FAILURE)
			return (SUCCESS);
	}
	return (FAILURE);
}
