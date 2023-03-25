/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_on.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:06:34 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/02/14 12:06:37 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ert				_count_atoi(const char *str, int *nb_pt);
static const char	*ft_skipspace(const char *ptr);

t_ert	ft_atoi_on(const char *str, int *nb_pt)
{
	*nb_pt = 1;
	str = ft_skipspace(str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*nb_pt = -1;
		str++;
	}
	if (*str == 0)
		return (FAILURE);
	return (_count_atoi(str, nb_pt));
}

t_ert	_count_atoi(const char *str, int *nb_pt)
{
	int	counter;
	int	res;

	res = 0;
	while (*str != ' ' && *str)
	{
		counter = 0;
		while ("0123456789"[counter] != *str && counter < 10)
			counter++;
		if (counter == 10 || (res * 10 + counter) * *nb_pt / 10 != res * *nb_pt)
			return (FAILURE);
		res = res * 10 + counter;
		str++;
	}
	*nb_pt *= res;
	return (SUCCESS);
}

static const char	*ft_skipspace(const char *ptr)
{
	char	*set;

	set = " \t\f\r\v\n";
	while (*set)
	{
		if (*ptr == *set)
		{
			ptr++;
			set = " \t\f\r\v\n";
		}
		else
			set++;
	}
	return (ptr);
}
