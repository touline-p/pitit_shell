/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:41:19 by twang             #+#    #+#             */
/*   Updated: 2023/05/12 10:13:42 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_check_line(char *line);
static int				_get_alloc_size(char *line);
static	t_return_status	_find_matching_files(char *line, char *name);

/*----------------------------------------------------------------------------*/

t_return_status	parse_args(char *line)
{
	// char **match;
	int	size;

	
	// match = NULL;
	size = 0;
	if (_check_line(line) != SUCCESS)
		return (FAILURE);
	size = _get_alloc_size(line);
	if (size <= 0)
		return (FAILURE);
	// match = ft_calloc(size + 1, sizeof(char *));
	// if (match)
		// return (FAILURE);
	// match = fetch_matching_files(line);
	return (SUCCESS);
}

static t_return_status	_check_line(char *line)
{
	int	nb_of_stars;

	nb_of_stars = 0;
	while (*line)
	{
		if (*line == '*')
			nb_of_stars++;
		if (*line == '/')
		{
			ft_dprintf(2, RED"minishell: /: bonus wildcards can be used only \
			in the current directory\n"END);
			return (FAILURE);
		}
		line++;
	}
	if (nb_of_stars <= 0)
		return (FAILURE);
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
		{
			printf(GREEN"%s\n"END, data->d_name);
			size++;
		}
	}
	closedir(directory);
	printf("%d\n", size);
	return (size);
}

static	t_return_status	_find_matching_files(char *line, char *name)
{

	while (*line)
	{
		while (*line == '*' && *(line + 1) == '*')
			line++;
		if (*line == '*')
		{
			line++;
 			name = ft_strstr_w(name, line);
		}
		if (*line)
			return (SUCCESS);
		if (!name || (*line && *line != '*' && *name != *line))
		{
			return (FAILURE);
		}
		line++;
		name++;
	}
	return (SUCCESS);
}

# define TEST_SA_MERE
# ifdef TEST_SA_MERE

int main(void)
{
	char *line = "li*";

	if (parse_args(line) != SUCCESS)
		puts("voili");
}

#endif