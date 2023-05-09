/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:27:19 by twang             #+#    #+#             */
/*   Updated: 2023/05/09 19:50:56 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static	t_return_status	find_matching_files(t_w_data *w_data, char *line, \
char *name);
static t_return_status	where_is_the_star(t_w_data *w_data, char *line, \
char *name);
static t_return_status	where_are_the_stars(t_w_data *w_data, char *line, \
char *name);

/*----------------------------------------------------------------------------*/

t_return_status	get_wild_args(char *line)
{
	t_w_data		w_data;
	struct dirent	*data;
	DIR				*directory;
	int				size;

	size = 0;
	directory = opendir(".");
	if (!directory)
	{
		perror ("minishell: opendir: cannot open current directory");
		return (FAILURE);
	}
	bzero(&w_data, sizeof(t_w_data));
	if (check_line(&w_data, line) != SUCCESS)
		return (FAILURE);
	while (1)
	{
		data = readdir(directory);
		if (data == NULL)
			break ;
		if (find_matching_files(&w_data, line, data->d_name) == SUCCESS)
			size++;
	}
	closedir(directory);
	ft_dprintf(2, GREEN"size alloc :%d\n"END, size);
	return (SUCCESS);
}

static	t_return_status	find_matching_files(t_w_data *w_data, char *line, \
											char *name)
{
	if (w_data->nb_of_stars == 1)
	{
		if (where_is_the_star(w_data, line, name) != FAILURE)
			return (SUCCESS);
	}
	else
	{
		if (where_are_the_stars(w_data, line, name) != FAILURE)
			return (SUCCESS);
	}
	return (FAILURE);
}

static t_return_status	where_is_the_star(t_w_data *w_data, char *line, \
											char *name)
{
	if (strcmp(line, "*") == 0)
	{
		if (name[0] != '.')
		{
			printf("%s\n", name);
			return (SUCCESS);
		}
	}
	else if (w_data->first == '*')
	{
		line++;
		if (ft_strnstr(name, line, ft_strlen(line)) != NULL)
			printf("%s\n", name);
	}
	else if (w_data->last == '*')
		puts("il n'y a que une etoile et elle est a la fin");
	else
		puts("il va falloir split ???");
	return (FAILURE);
}

static t_return_status	where_are_the_stars(t_w_data *w_data, char *line, \
											char *name)
{
	(void)w_data;
	(void)line;
	(void)name;
	puts("nana");
	return (FAILURE);
}

#define TST_WILD
#ifdef TST_WILD

int	main(int ac, char **av)
{
	(void)ac; (void)av;
	char *line = "*l";

	get_wild_args(line);
	return (0);
}

#endif

/*TODO: lire la ligne et check nombre + types char pour savoir quelle direction prendre
	- combien d'etoiles 
	- get premier et derniere char : tout entre gere par split
	- si il y a un / -> error */
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
