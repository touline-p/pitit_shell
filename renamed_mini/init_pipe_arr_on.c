/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe_arr_on.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:20:16 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/10 22:38:23 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by bpoumeau on 3/10/23.
//
#include "mini_parsing.h"

static size_t	_get_nb_pipe(t_string_token *tok);
static t_ert	_allocate_pipe_arr(int **pipe_arr_pt, size_t nb_pipes);
static t_ert	_pipe_all_this_cells(int **pipe_arr_pt);
static t_ert	_allocate_pipe_arr_ep(int **start_pt, int **arr_adrss, t_ert ret_val);

t_ert	init_pipe_arr_on(int ***pipe_arr_pt, t_string_token *tok)
{
	size_t	nb_pipes;

	nb_pipes = _get_nb_pipe(tok);
	*pipe_arr_pt = malloc(sizeof(int*) * (nb_pipes + 1));
	if (pipe_arr_pt == NULL
		|| _allocate_pipe_arr(*pipe_arr_pt, nb_pipes) != SUCCESS
		|| _pipe_all_this_cells(*pipe_arr_pt) != SUCCESS)
		return (_allocate_pipe_arr_ep(*pipe_arr_pt, *pipe_arr_pt, FAILURE));
	printf("i succeeded\n");
	return (SUCCESS);
}

static size_t	_get_nb_pipe(t_string_token *tok)
{
	size_t	i;

	i = 0;
	while (tok->token != EOL)
	{
		if (tok->token == PIPE)
			i++;
		tok = tok->next;
	}
	printf("they are %ld pipes\n", i);
	return (i);
}

static t_ert	_allocate_pipe_arr(int **pipe_arr_pt, size_t nb_pipes)
{
	pipe_arr_pt[nb_pipes] = NULL;
	while (nb_pipes--)
	{
		pipe_arr_pt[nb_pipes] = malloc(sizeof(int) * 2);
		if (pipe_arr_pt[nb_pipes] == NULL)
			return (_allocate_pipe_arr_ep(&pipe_arr_pt[nb_pipes], pipe_arr_pt, FAILURE));
	}
	return (SUCCESS);
}

static t_ert	_allocate_pipe_arr_ep(int **start_pt, int **arr_adrss, t_ert ret_val)
{
	while (*start_pt)
	{
		free(*start_pt);
		start_pt++;
	}
	free(arr_adrss);
	return (ret_val);
}

static t_ert	_pipe_all_this_cells(int **pipe_arr_pt)
{
	while (*pipe_arr_pt)
	{
		if (pipe(*pipe_arr_pt) != 0)
			return (close_pipe_arr(pipe_arr_pt), FAILURE);
		pipe_arr_pt++;
	}
	return (SUCCESS);
}