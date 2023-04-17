/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:58:30 by twang             #+#    #+#             */
/*   Updated: 2023/04/17 10:33:33 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	s_length(char *s1, char *s2)
{
	size_t	join_length;
	size_t	s1_length;
	size_t	s2_length;

	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	join_length = s1_length + s2_length;
	return (join_length);
}

char	*strjoin_path_cmd(char *s1, char *s2)
{
	size_t	length;
	char	*s_join;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
		s2 = ft_calloc(1, sizeof(char));
	length = s_length((char *)s1, (char *)s2);
	s_join = ft_calloc(length + 1, sizeof(char));
	if (!s_join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s_join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s_join[i + j] = s2[j];
		j++;
	}
	free(s1);
	return (s_join);
}