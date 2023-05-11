/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switchman.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:35:42 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/05/09 22:35:49 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_parsing.h"

size_t	go_to_next_(t_emt token, t_string_token *tmp, t_string_token **str_tok)
{
	size_t	l;

	l = 0;
	if (tmp == NULL)
		return (INT_MAX);
	while (tmp->token != token && tmp->token != EOL)
	{
		if (tmp->token == O_PRTSS)
			l += go_to_next_(C_PRTSS, tmp->next, &tmp);
		else
		{
			tmp = tmp->next;
			l++;
		}
	}
	*str_tok = tmp;
	return (l);
}

void	go_to_next_logical_door(t_string_token *src, t_string_token **dst)
{
	t_string_token	*and_pt;
	t_string_token	*or_pt;
	size_t			and_l;
	size_t			or_l;

	and_l = go_to_next_(AND, src->next, &and_pt);
	or_l = go_to_next_(OR, src->next, &or_pt);
	if (and_l < or_l)
		*dst = and_pt;
	else
		*dst = or_pt;
}

size_t	count_instructions_node(t_string_token *str_tok_lst)
{
	size_t			count;
	t_string_token	*tmp;

	count = 0;
	tmp = str_tok_lst;
	while (tmp->token != EOL)
	{
		count++;
		go_to_next_logical_door(tmp->next, &tmp);
	}
	return (count);
}

t_return_status	fill(t_string_token **instructions_arr, \
					t_string_token *str_tok_lst)
{
	size_t			i;
	t_string_token	*next;

	i = 0;
	while (str_tok_lst->token != EOL)
	{
		instructions_arr[i++] = str_tok_lst;
		go_to_next_logical_door(str_tok_lst, &next);
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

int	_get_next_index(int last, t_string_token **instructions_arr)
{
	t_emt	to_search;

	to_search = AND;
	if (last == -1)
		return (0);
	if (g_ret_val != 0)
		to_search = OR;
	while (instructions_arr[last] && instructions_arr[last]->token != to_search)
		string_token_destructor(instructions_arr[last++]);
	if (instructions_arr[last])
		return (last);
	return (-1);
}

//void	clean_last_string_tokens_lst(t_string_token **instructions_arr, int index)
//{
//	while (instructions_arr[index])
//	{
//		string_token_destructor(instructions_arr[index]);
//		index++;
//	}
//}

t_return_status	launch_instructions_arr(t_data *data, \
						t_string_token **instructions_arr, char ***env)
{
	t_string_token	*actual;

	data->index = 0;
	while (data->index != -1)
	{
		actual = instructions_arr[data->index];
		execution(data, actual, env);
		data->index = _get_next_index(++data->index, instructions_arr);
		if (g_ret_val == 2)
			return (SUCCESS);
	}
//	clean_last_string_tokens_lst(instructions_arr, data->index);
	free(instructions_arr);
	return (SUCCESS);
}

t_return_status	switchman(t_data *data, \
					t_string_token *token_lst, char ***env_pt)
{
	if (data->instructions_arr != NULL)
		free(data->instructions_arr);
	data->instructions_arr = malloc(sizeof(t_string_token *) \
				* (count_instructions_node(token_lst) + 1));
	if (data->instructions_arr == NULL)
		return (FAILURE);
	fill(data->instructions_arr, token_lst);
	/*
	printf("decoupage de chaque bloc\n");
	int i  = 0;
	while (data->instructions_arr[i])
	{
		display_str_token(data->instructions_arr[i++]);
	}
	 */
	launch_instructions_arr(data, data->instructions_arr, env_pt);
	return (SUCCESS);
}
