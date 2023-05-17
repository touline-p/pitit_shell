/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:27:19 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 17:15:04 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_fetch_on(char *line, char ***dst_arr);
static t_return_status	_expand_wildcards_error(char ***new);
static char				**joined_new(char ***new);
static int				_size_origin(char ***new);

/*----------------------------------------------------------------------------*/

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
		if (_fetch_on(original_array[i], &new[i]) != SUCCESS)
			return (_expand_wildcards_error(new));
		i++;
	}
	free(original_array);
	*original_pt = joined_new(new);
	return (SUCCESS);
}

static t_return_status	_fetch_on(char *line, char ***dst_arr)
{
	int	size;

	size = 0;
	if (check_line(line) != SUCCESS)
		return (FAILURE);
	size = get_alloc_size(line);
	if (size <= 0)
		return (FAILURE);
	*dst_arr = ft_calloc(size + 1, sizeof(char *));
	if (*dst_arr == NULL)
		return (FAILURE);
	if (fill_dst_arr(line, *dst_arr) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static t_return_status	_expand_wildcards_error(char ***new)
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

static char	**joined_new(char ***new)
{
	int		i;
	int		j;
	int		k;
	char	**dst;

	dst = ft_calloc(_size_origin(new), sizeof(char *));
	if (!dst)
		return (NULL);
	i = 0;
	k = 0;
	while (new[i])
	{
		j = 0;
		while (new[i][j])
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

static int	_size_origin(char ***new)
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
