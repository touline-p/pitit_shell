/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:03:32 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 09:54:53 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"
#include "../../../incs/minishell.h"
#include "../../../incs/minishell.h"
#include "../../../incs/minishell.h"

/*---- prototypes ------------------------------------------------------------*/

// static	t_return_status	_find_matching_files(char *line, char *name);

/*----------------------------------------------------------------------------*/

t_return_status	check_line(char *line)
{
	int	nb_of_stars;

	nb_of_stars = 0;
	while (*line)
	{
		if (*line == - '*')
			nb_of_stars++;
		if (*line == '/' && nb_of_stars > 0)
		{
			ft_dprintf(2, RED"minishell: /: wildcards can be used only");
			ft_dprintf(2, " in the current directory\n"END);
			return (SUCCESS);
		}
		line++;
	}
	return (SUCCESS);
}

int	get_alloc_size(char *line)
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
		if (find_matching_files(line, data->d_name) == SUCCESS)
			size++;
	}
	closedir(directory);
	if (size == 0)
		return (1);
	return (size);
}

t_return_status	find_matching_files(char *line, char *name)
{
	if ((name[0] == '.' && line[0] != '.')
		|| (line[0] == '.' && name[0] != '.')
		|| (ft_strchr(line, - '*') == NULL))
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
			return (FAILURE);
		line++;
		name++;
	}
	return (SUCCESS);
}

void	replace_wild_card(char *line)
{
	while (*line)
	{
		if (*line == - '*')
			*line = '*';
		line++;
	}
}

static t_return_status	_fill_dst_arr_one_name(char *line, \
							char **arr_to_fill, int *i)
{
	struct dirent	*data;
	DIR				*directory;

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
		if (find_matching_files(line, data->d_name) == SUCCESS)
		{
			arr_to_fill[*i] = ft_strdup(data->d_name);
			if (arr_to_fill[*i] == NULL)
				return (FAILURE);
			(*i)++;
		}
	}
	closedir(directory);
	return (SUCCESS);
}

t_return_status	fill_dst_arr(char *line, char **arr_to_fill)
{
	int				i;

	i = 0;
	_fill_dst_arr_one_name(line, arr_to_fill, &i);
	if (i == 0)
	{
		replace_wild_card(line);
		arr_to_fill[i] = ft_strdup(line);
	}
	free(line);
	return (SUCCESS);
}
