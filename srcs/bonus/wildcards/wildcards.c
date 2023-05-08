/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:27:19 by twang             #+#    #+#             */
/*   Updated: 2023/05/08 20:06:42 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static	t_return_status	find_corresponding_files(char *line, char *name);

/*----------------------------------------------------------------------------*/

/*
t_return_status	wildcard_management(char ***av)
{
	char	**original;
	char	***

	original = *av;
	if(check_original(original) == false)
		return (SUCCESS);

}
*/

t_return_status	get_wild_args(char *line)
{
	DIR				*directory;
	struct dirent	*data;
	int				size;
	
	size = 0;
	if ((directory = opendir(".")) != NULL)
	{
		while ((data = readdir(directory)))
		{
			if (find_corresponding_files(line, data->d_name) == SUCCESS)
				size++;
		}
		closedir(directory);
	}
	else
	{
		perror ("minishell: opendir: cannot open current directory");
		return (FAILURE);
	}
	ft_dprintf(2, "%d\n", size);
	return (SUCCESS);
}

static	t_return_status	find_corresponding_files(char *line, char *name)
{
	char	**files;
	int		i;
	
	files = NULL;
	i = 0;
	// printf("%s\n", name);
	if (ft_strcmp(line, "*") == 0)
	{
		if (name[0] != '.')
		{
			return (SUCCESS);
		}
	}
	files = ft_split(line, '*');
	while (files[i])
	{
		if ((strstr(files[i], name)) == NULL)
		{
			puts("nope");
			printf("files[i]: %s \tname: %s\n", files[i], name);
		}
		i++;
	}
	return (SUCCESS);
	// ft_print_split(files);
}

#define TST_WILD
#ifdef TST_WILD

int main(int ac, char **av)
{
	(void)ac; (void)av;
	char *line = "*li";

	get_wild_args(line);
	return (0);
}

#endif
