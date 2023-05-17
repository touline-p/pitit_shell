/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:38:17 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 13:35:04 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "minishell_execution.h"
#include "structures_execution.h"
#include <readline/readline.h>
#include "../incs/execution_incs/minishell_execution.h"
#include "../incs/parsing_incs/minishell_parsing.h"

/*---- global definition -----------------------------------------------------*/

int	g_ret_val;

/*----------------------------------------------------------------------------*/

#define MAIN
#ifdef MAIN

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_welcome_to_minihell(char ***env_pt);
static int				_go_fuck_yourself_malloc(t_string_token *string_token, \
												char **env);

/*----------------------------------------------------------------------------*/

# define IT_DOES_NOT_WORK 0


t_return_status reset_term_settings(t_data *data)
{
	if (tcsetattr(1, TCSANOW, &data->term) == -1)
	{
		perror("tcsetattr");
		errno = SUCCESS;
	}
	return (SUCCESS);
}

t_return_status	init_main(t_data *data, t_string_token **str_token_pt, \
				char **av, char ***env_pt)
{
	data->prompt = NULL;
	data->instructions_arr = NULL;
	*str_token_pt = NULL;
	if (check_arguments(av) != SUCCESS
		|| _welcome_to_minihell(env_pt) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);

}

void	loop_init(t_data *data, char **line_pt, char **env)
{
	init_signals(data);
	if (get_prompt_on(&(data->prompt), env) != SUCCESS)
		clean_the_prompt(data->prompt, *line_pt, env);
	*line_pt = readline(data->prompt);
	errno = 0;
	if ((*line_pt == NULL) || ft_strcmp("", *line_pt))
		clean_the_prompt(data->prompt, *line_pt, env);
	add_history(*line_pt);
}

t_return_status set_data_instruction_arr(t_data *data, t_string_token *str_tok_lst)
{
	data->instructions_arr = malloc(sizeof(t_string_token *) * 2);
	if (data->instructions_arr == NULL)
		return (FAILED_MALLOC);
	data->instructions_arr[0] = str_tok_lst;
	data->instructions_arr[1] = NULL;
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_data			data;
	t_string_token	*str_tok_lst;

	(void)ac;
	if (init_main(&data, &str_tok_lst, av, &env) != SUCCESS)
		return (1);
	while (MINI_SHELL_MUST_GO_ON)
	{
		loop_init(&data, &line, env);
		if (get_lexed_str_token_lst_from_line(line, &str_tok_lst, env) \
			!= SUCCESS)
			continue ;
		if (set_data_instruction_arr(&data, str_tok_lst))
			return (_go_fuck_yourself_malloc(str_tok_lst, env));
		if (heredoc_management(&data, str_tok_lst, env)
			&& reset_term_settings(&data) == SUCCESS)
			continue ;
		reset_term_settings(&data);
		switchman(&data, str_tok_lst, &env);
	}
}

static t_return_status	_welcome_to_minihell(char ***env_pt)
{
	g_ret_val = 0;
	if (env_init_on(env_pt) != SUCCESS)
		return (FAILED_MALLOC);
	ft_dprintf(2, PURPLE"%s%s", START_MSG_00, START_MSG_01);
	ft_dprintf(2, "%s%s", START_MSG_02, START_MSG_03);
	ft_dprintf(2, "%s%s", START_MSG_04, START_MSG_05);
	ft_dprintf(2, "%s%s%s", START_MSG_06, START_MSG_07, START_MSG_08);
	ft_dprintf(2, "%s%s%s", START_MSG_09, START_MSG_10, START_MSG_11);
	ft_dprintf(2, "%s%s", START_MSG_12, START_MSG_13);
	ft_dprintf(2, "%s%s", START_MSG_00, START_MSG_01);
	ft_dprintf(2, ITALIC"%s"END, START_MSG_14);
	return (SUCCESS);
}

static int	_go_fuck_yourself_malloc(t_string_token *token_lst, char **env)
{
	ft_free_split(env);
	string_token_destructor(token_lst);
	printf("DAMMIT, memory is shit\n");
	return (IT_DOES_NOT_WORK);
}

#endif
