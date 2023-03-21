/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:43:18 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/21 13:53:55 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by bpoumeau on 2/15/23.
//

#include "libft.h"

void	ft_lstclean(t_list *head, void (*del)(void *))
{
	t_list	*pin;

	pin = NULL;
	while (head)
	{
		pin = head->next;
		del(head->content);
		free(head);
		head = pin;
	}
}

//t_ert	ft_lstnew_on(void *content, t_list **list_ptr)
//{
//	t_list	*new;
//
//	new = malloc(sizeof (t_list));
//	if (new == NULL)
//		return (MLC_ERR);
//	new->content = content;
//	new->next = NULL;
//	*list_ptr = new;
//	return (SUCCESS);
//}
//
//t_ert	ft_lstnew_onsf(void *content, t_list **list_ptr)
//{
//	if (content == NULL)
//		return (MLC_ERR);
//	return (ft_lstnew_on(content, list_ptr));
//}
