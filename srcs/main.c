/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:53:30 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/27 18:25:55 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "minishell_execution.h"
#include "structures_execution.h"
#include <readline/readline.h>

/*---- prototypes ------------------------------------------------------------*/

t_return_status get_lexed_str_token_lst_from_line(char *line, t_string_token **str_tok_pt, char **env);

/*----------------------------------------------------------------------------*/


int	main(int ac, char **av, char **env)
{
	char	*line;
	t_string_token	*str_tok_lst;
	(void)ac; (void)av;

	line = readline(PURPLE"Y a quoi ? : "END);
	printf("j'ai lu ->%s<-\n", line);
	get_lexed_str_token_lst_from_line(line, &str_tok_lst, env);
	display_str_token(str_tok_lst);
	execution(str_tok_lst);
	return (0);
}
