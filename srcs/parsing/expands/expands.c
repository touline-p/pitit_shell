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

#include "minishell_parsing.h"
/*
t_ret_status	performe_expand_on_line(char **line_pt, char **env)
{
	char **line_arr;
	char **pin;

	if (cut_line_on(*line_pt, &line_arr) != SUCCESS)
		return (0);
	printf("i m here\n");
	pin = line_arr;
	while (pin && *pin)
	{
		if (**pin == '$' && \
		replace_dollar_str_by_env_value(pin, env) != SUCCESS)
			return (FAILED_MALLOC);
		pin++;
	}
	if (ft_join_str_arr_on(line_arr, line_pt) != SUCCESS)
		return (ft_free_split(line_arr), FAILED_MALLOC);
	ft_free_split(line_arr);
	return (SUCCESS);
}

// #define TST_EXPAND
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
*/