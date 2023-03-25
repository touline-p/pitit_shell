/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:21:25 by bpoumeau          #+#    #+#             */
/*   Updated: 2022/11/08 13:44:50 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strdup(const char *src)
{
	char	*dst;
	char	*tmp;

	tmp = (char *)src;
	while (*tmp)
		tmp++;
	dst = malloc(tmp - src + 1);
	if (!dst)
		return (NULL);
	tmp = dst;
	while (*src)
		*(tmp++) = *(src++);
	*tmp = 0;
	return (dst);
}

t_ret_status	ft_strdup_on(const char *src, char **str_pt)
{
	char *new;

	new = ft_strdup(src);
	if (new == NULL)
		return (FAILED_MALLOC);
	*str_pt = new;
	return (SUCCESS);
}
