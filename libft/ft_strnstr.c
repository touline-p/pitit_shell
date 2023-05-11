/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:21:43 by twang             #+#    #+#             */
/*   Updated: 2023/05/11 14:19:02 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*hayst;
	char	*needl;

	i = 0;
	hayst = (char *)haystack;
	needl = (char *)needle;
	if (!needl[i])
		return (hayst);
	while (i < len && hayst[i])
	{
		j = 0;
		while (hayst[i + j] == needl[j] && i + j < len)
		{
			if (needl[j + 1] == '\0')
				return ((char *) &hayst[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strstr_w(char *haystack, char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[i])
		return (haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '*' || (needle[j] == '\0' && haystack[i + j] == '\0'))
			{
				return ((char *) &haystack[i]);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
