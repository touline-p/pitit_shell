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


t_return_status	performe_expand_on_line(char **line_pt, char **env)
{
	char **line_arr;
	char **pin;

	printf("%p\n", *line_pt);
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

	pin = token_lst->next;
	while (pin->token != EOL)
	{
		printf("expand for args %s\n", pin->content);
		if (performe_expand_on_line(&(pin->content), env) != SUCCESS)
			return (FAILED_MALLOC);
		pin = pin->next;
	}
	if (split_t_string_token_on_space(token_lst->next) != SUCCESS)
		return (FAILED_MALLOC);
	del_empty_tokens(token_lst);
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

#define TST_EXPAND_FOR_ARGS
#ifdef TST_EXPAND_FOR_ARGS

int	main(int ac, char **av, char **env)
{
	(void)ac;
	t_string_token	*str_token;
	av[1] = ft_strdup(av[1]);
	get_lexed_str_token_lst_from_line(av[1], &str_token, env);
	free(av[1]);
	display_str_token(str_token);
	expand_for_args(str_token, env);
	display_str_token(str_token);
	string_token_destructor(str_token);
	return (0);
}

#endif