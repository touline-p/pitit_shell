/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:54:46 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/02/16 03:26:41 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_ert	_read_into_lst(int fd, t_list *head, char *buffer);
static t_ert	_gnl_ep(t_list *head, t_ert ert);

t_ert	ft_gnl_on(int fd, char **line_pt)
{
	static char	buffer[BUFFER_SIZE + 1];
	t_list		*head;

	if (ft_lstnew_onsf(ft_strdup(buffer), &head) != SUCCESS)
		return (ft_memcset(buffer, 0, 0, BUFFER_SIZE), MLC_ERR);
	ft_memcset(buffer, 0, 0, BUFFER_SIZE);
	if (_read_into_lst(fd, head, buffer) != SUCCESS)
		return (_gnl_ep(head, MLC_ERR));
	if (ft_lststr_to_str(head, line_pt) != SUCCESS)
		return (_gnl_ep(head, MLC_ERR));
	if (**line_pt == 0)
	{
		free(*line_pt);
		*line_pt = NULL;
	}
	return (_gnl_ep(head, SUCCESS));
}

static t_ert	_read_into_lst(int fd, t_list *head, char *buffer)
{
	t_list	*pin;
	char	*endl_pt;
	int		signal;

	pin = head;
	signal = BUFFER_SIZE;
	while (ft_strchr(pin->content, '\n') == NULL && signal == BUFFER_SIZE)
	{
		if (ft_lstnew_onsf(malloc(BUFFER_SIZE + 1), &(pin->next)) != SUCCESS)
			return (MLC_ERR);
		pin = pin->next;
		signal = read(fd, pin->content, BUFFER_SIZE);
		if (signal == -1)
			return (FAILURE);
		((char *)(pin->content))[signal] = 0;
	}
	endl_pt = ft_strchr(pin->content, '\n');
	if (endl_pt)
	{
		ft_strcpy(buffer, endl_pt + 1);
		endl_pt[1] = 0;
	}
	return (SUCCESS);
}

static t_ert	_gnl_ep(t_list *head, t_ert ert)
{
	ft_lstclean(head, free);
	return (ert);
}
