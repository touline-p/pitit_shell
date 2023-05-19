/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switchman.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:35:42 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/17 17:13:45 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---- prototypes ------------------------------------------------------------*/

static size_t			_count_instructions_node(t_string_token *str_tok_lst);
static t_return_status	_fill(t_string_token **instructions_arr, \
					t_string_token *str_tok_lst);
static t_return_status	_launch_instructions_arr(t_data *data, \
						t_string_token **instructions_arr, char ***env);

/*----------------------------------------------------------------------------*/

t_return_status	switchman(t_data *data, \
					t_string_token *token_lst, char ***env_pt)
{
	if (data->instructions_arr != NULL)
		free(data->instructions_arr);
	data->instructions_arr = malloc(sizeof(t_string_token *) \
				* (_count_instructions_node(token_lst) + 1));
	if (data->instructions_arr == NULL)
		return (FAILURE);
	_fill(data->instructions_arr, token_lst);
	_launch_instructions_arr(data, data->instructions_arr, env_pt);
	return (SUCCESS);
}

static size_t	_count_instructions_node(t_string_token *str_tok_lst)
{
	size_t			count;
	t_string_token	*tmp;

	count = 0;
	tmp = str_tok_lst;
	while (tmp->next != NULL)
	{
		count++;
		go_to_next_logical_door(tmp->next, &tmp);
	}
	return (count);
}

static t_return_status	_fill(t_string_token **instructions_arr, \
					t_string_token *str_tok_lst)
{
	size_t			i;
	t_string_token	*next;

	i = 0;
	while (str_tok_lst->token != EOL)
	{
		instructions_arr[i++] = str_tok_lst;
		go_to_next_logical_door(str_tok_lst->next, &next);
		while (str_tok_lst->next != next)
			str_tok_lst = str_tok_lst->next;
		if (str_tok_lst->next->token != EOL)
		{
			str_tok_lst->next = string_token_creator();
			str_tok_lst->next->token = EOL;
			str_tok_lst->next->next = NULL;
		}
		str_tok_lst = next;
	}
	instructions_arr[i] = NULL;
	return (SUCCESS);
}

static t_return_status	_free_minishell_data(t_data *data)
{
	free(data->instructions_arr);
	free(data->cmds_block);
}

static t_return_status	_launch_instructions_arr(t_data *data, \
						t_string_token **instructions_arr, char ***env)
{
	t_string_token	*actual;

	data->index = 0;
	while (data->index != -1)
	{
		actual = instructions_arr[data->index];
		if (execution(data, actual, env) != SUCCESS)
			return (_free_minishell_data(data), FAILED_MALLOC);
		data->index = get_next_index(++data->index, instructions_arr);
		if (g_ret_val == 2)
			return (SUCCESS);
	}
	free(instructions_arr);
	return (SUCCESS);
}
