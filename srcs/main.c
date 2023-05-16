/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:38:17 by twang             #+#    #+#             */
/*   Updated: 2023/05/16 18:56:20 by twang            ###   ########.fr       */
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
static int				_go_fuck_yourself_malloc(void);

/*----------------------------------------------------------------------------*/

# define IT_DOES_NOT_WORK 0

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_data			data;
	t_string_token	*str_tok_lst;

	data.prompt = NULL;
	data.instructions_arr = NULL;
	line = NULL;
	str_tok_lst = NULL;
	if (check_arguments(ac, av) != SUCCESS)
		return (1);
	if (_welcome_to_minihell(&env) != SUCCESS)
		return (1);
	while (MINI_SHELL_MUST_GO_ON)
	{
		init_signals();
		get_prompt_on(&(data.prompt), env);
		line = readline(data.prompt);
		errno = 0;
		if (line == NULL || ft_strcmp("", line) == 0)
		{
			clean_the_prompt(data.prompt, line, env);
			continue ;
		}
		add_history(line);
		if (get_lexed_str_token_lst_from_line(line, &str_tok_lst, env) \
			!= SUCCESS)
			continue ;
		del_space_token(str_tok_lst);
		data.instructions_arr = malloc(sizeof(t_string_token *) * 2);
		if (data.instructions_arr == NULL)
			return (_go_fuck_yourself_malloc());
		data.instructions_arr[0] = str_tok_lst;
		data.instructions_arr[1] = NULL;
		del_space_token(str_tok_lst);
		if (heredoc_management(&data, str_tok_lst, env))
			continue ;
		switchman(&data, str_tok_lst, &env);
	}
	return (0);
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

static int	_go_fuck_yourself_malloc(void)
{
	printf("DAMMIT, memory is shit\n");
	return (IT_DOES_NOT_WORK);
}

#endif
