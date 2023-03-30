/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:22:46 by twang             #+#    #+#             */
/*   Updated: 2023/03/21 18:02:40 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static t_return_status	_expand_str_and_split_space(t_string_token **pin_pt, char **env);

t_return_status	performe_expand_on_line(char **line_pt, char **env)
{
	char **line_arr;
	char **pin;

	if (cut_line_on(*line_pt, &line_arr) != SUCCESS)
		return (0);
	pin = line_arr;
	while (pin && *pin)
	{
		if (**pin == '$' && \
		replace_dollar_str_by_env_value(pin, env) != SUCCESS)
			return (ft_free_split(line_arr), FAILED_MALLOC);
		pin++;
	}
	if (ft_join_str_arr_on(line_arr, line_pt) != SUCCESS)
		return (ft_free_split(line_arr), FAILED_MALLOC);
	ft_free_split(line_arr);
	return (SUCCESS);
}

t_return_status	expand_for_args(t_string_token *token_lst, char **env)
{
	t_string_token	*pin;

	pin = token_lst;
	while (pin->token != EOL)
		if (_expand_str_and_split_space(&pin, env) != SUCCESS)
			return (FAILED_MALLOC);
	del_empty_tokens(token_lst);
	return (SUCCESS);
}

static t_return_status	_expand_str_and_split_space(t_string_token **pin_pt, char **env)
{
	t_string_token	*tmp;

	tmp = *pin_pt;
	*pin_pt = tmp->next;
	if (performe_expand_on_line(&(tmp->content), env) != SUCCESS)
		return (FAILED_MALLOC);
	if (split_t_string_token_on_space(&tmp) != SUCCESS)
		return (FAILED_MALLOC);
	return (SUCCESS);
}

#ifdef TST_EXPAND

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	char *line = ft_strdup("expand qui marche $USERU $test");
	printf("origine:\n->%s<-\n", line);
	if (performe_expand_on_line(&line, env) != SUCCESS)
		return (perror("allocation"), 1);
	printf("test:\n->%s<-\n", line);
	free(line);
	printf("I am so smart!\n");
	return (0);
}

#endif