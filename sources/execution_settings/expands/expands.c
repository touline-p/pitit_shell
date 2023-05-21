/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:22:46 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 19:26:46 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---- prototypes ------------------------------------------------------------*/

static bool		_check_emptyness(t_string_token *arg);
static size_t	_count_ln(t_string_token *token_lst);

/*----------------------------------------------------------------------------*/

t_return_status	join_token_lst_on(t_cmd *cmd, t_string_token **arg, char **env)
{
	char			**arr;
	char			*tmp;
	char			*ret;
	t_string_token	*token_lst;
	const char		*arrar[] = {"", NULL};

	token_lst = *arg;
	if (_check_emptyness((*arg)->next))
	{
		cmd->commands = ft_str_array_dup((char **)arrar);
		cmd->id_command = EMPTY;
		go_to_next_logical_door((*arg)->next, arg);
		return (SUCCESS);
	}
	tmp = malloc(_count_ln(token_lst) + 2);
	if (tmp == NULL)
		return (FAILED_MALLOC);
	ret = tmp;
	token_lst = token_lst->next;
	while (token_lst->token != EOL && token_lst->token != PIPE)
	{
		tmp = ft_strcpy_rn(tmp, token_lst->content);
		*(tmp++) = - ' ';
		token_lst = token_lst->next;
	}
	*tmp = 0;
	*arg = token_lst;
	if (cut_line_on(ret, &arr) != SUCCESS
		|| join_arr_on(arr, &ret, env))
		return (FAILED_MALLOC);
	arr = ft_split(ret, - ' ');
	free(ret);
	if (expand_wildcards(&arr) != SUCCESS)
		return (FAILED_MALLOC);
	if (*arr == NULL)
		return (FAILED_MALLOC);
	cmd->commands = arr;
	return (SUCCESS);
}

static bool	_check_emptyness(t_string_token *arg)
{
	char	*tmp;

	while (arg->token != EOL)
	{
		tmp = arg->content;
		while (*tmp)
		{
			if (*tmp > 0)
				return (false);
			tmp++;
		}
		arg = arg->next;
	}
	return (true);
}

static size_t	_count_ln(t_string_token *token_lst)
{
	size_t	count;

	count = 0;
	token_lst = token_lst->next;
	count += ft_strlen(token_lst->content);
	token_lst = token_lst->next;
	while (token_lst->token != EOL)
	{
		count += ft_strlen(token_lst->content);
		count++;
		token_lst = token_lst->next;
	}
	return (count);
}
