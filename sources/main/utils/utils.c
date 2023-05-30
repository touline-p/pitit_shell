/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:13:46 by twang             #+#    #+#             */
/*   Updated: 2023/05/30 17:06:34 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_return_status	reset_term_settings(t_data *data)
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
		|| welcome_to_minihell(env_pt) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

void	return_to_root(t_data *data, char *line, char **env)
{
	if (chdir("/") == -1)
	{
		perror("chdir");
		clean_the_prompt(data->prompt, line, env);
	}
	ft_dprintf(2, "You were lost\nPitit shell bring you back to root.\n");
	ft_dprintf(2, "Stop doing shit with directories pls.\n");
	ft_dprintf(2, "PWD won't be updated until you cd again.\n");
}

void	loop_init(t_data *data, char **line_pt, char **env)
{
	int		flag;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		return_to_root(data, *line_pt, env);
	free(tmp);
	flag = true;
	while (flag)
	{
		flag = false;
		init_signals(data);
		if (get_prompt_on(&(data->prompt), env) != SUCCESS)
			clean_the_prompt(data->prompt, *line_pt, env);
		*line_pt = readline(data->prompt);
		errno = 0;
		if (*line_pt == NULL)
			clean_the_prompt(data->prompt, *line_pt, env);
		if (ft_strcmp("", *line_pt) == 0)
			flag = true;
		if (ft_str_is_ascii(*line_pt) != true)
			continue ;
		add_history(*line_pt);
	}
	signal(SIGINT, &handle_signal_parent);
}

t_return_status	set_data_instruction_arr(t_data *data, \
											t_string_token *str_tok_lst)
{
	data->instructions_arr = malloc(sizeof(t_string_token *) * 2);
	if (data->instructions_arr == NULL)
		return (FAILED_MALLOC);
	data->instructions_arr[0] = str_tok_lst;
	data->instructions_arr[1] = NULL;
	return (SUCCESS);
}

int	go_fuck_yourself_malloc(t_string_token *token_lst, char **env)
{
	ft_free_split(env);
	string_token_destructor(token_lst);
	printf("DAMMIT, memory is shit\n");
	return (IT_DOES_NOT_WORK);
}
