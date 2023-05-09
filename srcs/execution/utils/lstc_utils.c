/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 06:09:11 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/20 06:09:15 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/execution_incs/minishell_execution.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

t_lstc	*init_lstc_first_read(int fd)
{
	char	buffer[1];
	t_lstc	*new;

	if (read(fd, buffer, 1) != 1)
		return (NULL);
	new = malloc(sizeof(t_lstc));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->c = *buffer;
	return (new);
}

t_lstc 	*lstc_clear(t_lstc *trash)
{
	t_lstc	*pin;

	while (trash->next)
	{
		pin = trash->next;
		free(trash);
		trash = pin;

	}
	free(trash);
	return (NULL);
}


t_lstc	*lstc_new(char c)
{
	t_lstc	*new;

	new = malloc(sizeof(t_lstc));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->c = c;
	return (new);
}

t_lstc	*read_lstc_from_fd(int fd)
{
	t_lstc	*lst;
	t_lstc	*tmp;
	char	buffer[1];
	int		signal;

	lst = init_lstc_first_read(fd);
	if (!lst)
		return (NULL);
	tmp = lst;
	signal = read(fd, buffer, 1);
	while (signal == 1)
	{
		tmp->next = lstc_new(*buffer);
		if (!tmp->next)
			return (lstc_clear(lst));
		tmp = tmp->next;
		signal = read(fd, buffer, 1);
	}
	if (signal == -1)
		return (lstc_clear(lst));
	return (lst);
}

void	lstc_cpy_in_str(t_lstc	*lst, char **str)
{
	char	*tmp;

	tmp = *str;
	while (lst)
	{
		*tmp++ = lst->c;
		lst = lst->next;
	}
	*tmp = 0;
}

size_t	lstc_size(t_lstc *lst)
{
	size_t	ret_val;

	ret_val = 0;
	while (lst)
	{
		lst = lst->next;
		ret_val++;
	}
	return (ret_val);
}

void read_lst(t_lstc *lst)
{
	while (lst)
	{
		lst = lst->next;
	}
}

t_return_status 	read_fd_in_str(int fd, char **dst)
{
	t_lstc	*lst;

	lst = read_lstc_from_fd(fd);
	read_lst(lst);
	if (lst == NULL)
	{
		*dst = ft_strdup("");
		if (errno)
			return (FAILURE);
		return (SUCCESS);
	}
	*dst = malloc(lstc_size(lst) + 1);
	if (*dst)
		lstc_cpy_in_str(lst, dst);
	lstc_clear(lst);
	return (SUCCESS);
}
