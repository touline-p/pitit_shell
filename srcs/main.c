/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:53:30 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/24 18:19:53 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "structures_execution.h"
#include <readline/readline.h>

t_return_status get_lexed_str_token_lst_from_line(char *line, t_string_token **str_tok_pt);

int	main(void)
{
	char	*line;
	t_string_token	*str_tok_lst;

	line = readline("Y a quoi ? :");
	printf("j'ai lu ->%s<-\n", line);
	get_lexed_str_token_lst_from_line(line, &str_tok_lst);
	display_str_token(str_tok_lst);
	return (0);
}