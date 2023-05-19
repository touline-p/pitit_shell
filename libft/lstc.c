//
// Created by bpoumeau on 5/19/23.
//

#include "libft.h"
#include "errno.h"


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

void	read_lst(t_lstc *lst)
{
	while (lst)
	{
		lst = lst->next;
	}
}

t_return_status	read_fd_in_str(int fd, char **dst)
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
