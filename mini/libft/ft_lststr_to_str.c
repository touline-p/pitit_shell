/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststr_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:19:13 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/02/15 20:53:10 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	_cpy_lst_in_str(t_list *lst, char *str);

t_ert	ft_lststr_to_str(t_list *lst, char **str_pt)
{
	int		len;
	char	*str;

	len = ft_lststrlen(lst);
	str = malloc(len + 1);
	if (str == NULL)
		return (MLC_ERR);
	_cpy_lst_in_str(lst, str);
	*str_pt = str;
	return (SUCCESS);
}

static void	_cpy_lst_in_str(t_list *lst, char *str)
{
	while (lst)
	{
		str = ft_strcpy_rn(str, lst->content);
		lst = lst->next;
	}
}

size_t	ft_lststrlen(t_list *lst)
{
	size_t	length;

	length = 0;
	while (lst)
	{
		length += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (length);
}
