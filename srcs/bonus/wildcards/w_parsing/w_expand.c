/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:58 by twang             #+#    #+#             */
/*   Updated: 2023/05/12 14:37:27 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"

static char **joined_new(char ***new);
static int	size_origin(char ***new);
static int	size_origin(char ***new);


static t_return_status	expand_wildcards_error(char ***new)
{
	int	i;

	i = 0;
	while (new[i])
	{
		ft_free_split(new[i]);
		i++;
	}
	free(new);
	return (FAILED_MALLOC);
}

t_return_status	expand_wildcards(char ***original_pt)
{
	
	int		i;
	char	***new;
	char	**original_array;
	
	original_array = *original_pt;
	new = ft_calloc(ft_str_array_len(original_array) + 1, sizeof(char **));
	if (!new)
		return (FAILED_MALLOC);
	i = 0;
	while (original_array[i])
	{
		if (fetch_on(original_array[i], &new[i]) != SUCCESS)
			return (expand_wildcards_error(new));
		i++;
	}
	free(original_array);
	*original_pt = joined_new(new);
	return (SUCCESS);
}

static char **joined_new(char ***new)
{
	int		i;
	int		j;
	int		k;
	char	**dst;

	dst = ft_calloc(size_origin(new), sizeof(char *));
	if (!dst)
		return (NULL);
	i = 0;
	k = 0;
	while (new[i])
	{
		j = 0;
		while(new[i][j])
		{
			dst[k] = new[i][j];
			j++;
			k++;
		}
		free(new[i]);
		i++;
	}
	free(new);
	return (dst);
}

static int	size_origin(char ***new)
{
	int	i;

	i = 0;
	while (*new)
	{
		i += ft_str_array_len(*new);
		new++;
	}
	i++;
	return (i);
}

//# define TEST_SA_MERE
# ifdef TEST_SA_MERE

int main(int ac, char **av, char **env)
{
	int i = 0;

	char	**bonjour = ft_str_array_dup(av);
	expand_wildcards(&bonjour);
	while (bonjour[i])
	{
		printf("%s\n", bonjour[i]);
		i++;
	}
	ft_free_split(bonjour);
	return 1;
}

#endif