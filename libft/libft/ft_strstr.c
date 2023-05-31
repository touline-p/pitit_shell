/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:57:22 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/10 01:57:24 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *big, char *little)
{
	size_t	little_size;

	while (*big)
	{
		if (ft_strncmp(big, little, ft_strlen(little)))
			return (big);
		big++;
	}
	return (NULL);
}
