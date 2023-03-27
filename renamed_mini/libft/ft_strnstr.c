/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:38:06 by bpoumeau          #+#    #+#             */
/*   Updated: 2022/11/10 21:22:56 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ret_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_strnstr(char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	lt_ln;

	i = 0;
	lt_ln = ft_strlen(little);
	if (!lt_ln)
		return (big);
	while (len >= lt_ln && big[i])
	{
		if (len < lt_ln)
			return (NULL);
		if (ft_strncmp(big + i, (char *)little, ret_min(lt_ln, len)) == 0)
			return (big + i);
		len--;
		i++;
	}
	return (NULL);
}
