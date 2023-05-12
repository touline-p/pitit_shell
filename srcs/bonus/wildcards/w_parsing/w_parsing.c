/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:41:19 by twang             #+#    #+#             */
/*   Updated: 2023/05/12 14:51:36 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_check_line(char *line);
static int				_get_alloc_size(char *line);
static	t_return_status	fill_dst_arr(char *line, char **arr_to_fill);
static	t_return_status	_find_matching_files(char *line, char *name);

/*----------------------------------------------------------------------------*/

t_return_status	fetch_on(char *line, char ***dst_arr)
{
	int	size;

	size = 0;
	if (_check_line(line) != SUCCESS)
		return (FAILURE);
	size = _get_alloc_size(line);
	if (size <= 0)
		return (FAILURE);
	*dst_arr = ft_calloc(size + 1, sizeof(char *));
	if (*dst_arr == NULL)
		 return (FAILURE);
	if (fill_dst_arr(line, *dst_arr) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static	t_return_status	fill_dst_arr(char *line, char **arr_to_fill)
{
	struct dirent	*data;
	DIR				*directory;
	int				i;
	
	i = 0;
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
		if (_find_matching_files(line, data->d_name) == SUCCESS)
		{
			arr_to_fill[i] = ft_strdup(data->d_name);
			if (arr_to_fill[i] == NULL)
				return (FAILURE);
			i++;
		}
	}
	if (i == 0)
		arr_to_fill[i] = ft_strdup(line);
	free(line);
	closedir(directory);
	return (SUCCESS);
}


static t_return_status	_check_line(char *line)
{
	int	nb_of_stars;

	nb_of_stars = 0;
	while (*line)
	{
		if (*line == - '*')
			nb_of_stars++;
		if (*line == '/' && nb_of_stars > 0)
		{
			ft_dprintf(2, RED"minishell: /: bonus wildcards can be used only \
			in the current directory\n"END);
			return (SUCCESS);
		}
		line++;
	}
	return (SUCCESS);
}

static int	_get_alloc_size(char *line)
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
		if (_find_matching_files(line, data->d_name) == SUCCESS)
			size++;
	}
	closedir(directory);
	if (size == 0)
		return (1);
	return (size);
}

static	t_return_status	_find_matching_files(char *line, char *name)
{
	if (name[0] == '.' && line[0] != '.')
		return (FAILURE);
	if (line[0] == '.' && name[0] != '.')
		return (FAILURE);
	if (ft_strchr(line, - '*') == NULL)
		return (FAILURE);
	while (*line)
	{
		while (*line == - '*' && *(line + 1) == - '*')
			line++;
		if (*line == - '*')
		{
			line++;
 			name = ft_strstr_w(name, line);
		}
		if (*line == 0)
			return (SUCCESS);
		if (!name || (*line && *line != - '*' && *name != *line))
		{
			return (FAILURE);
		}
		line++;
		name++;
	}
	return (SUCCESS);
}
