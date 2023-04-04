/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:53:30 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/04 16:11:28 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "minishell_execution.h"
#include "structures_execution.h"
#include <readline/readline.h>

/*---- prototypes ------------------------------------------------------------*/

t_return_status get_lexed_str_token_lst_from_line(char *line, t_string_token **str_tok_pt, char **env);

/*----------------------------------------------------------------------------*/
#define MAIN
#ifdef MAIN
static void	welcome_to_minihell(void)
{
	printf(ITALIC BLUE"\nThis is madness\n\n"END);
	printf(BLUE"by ⭐ \e]8;;https://profile.intra.42.fr/users/bpoumeau\a\e[34mbpoumeau\e[34m\e]8;;\a ");
	printf("& \e]8;;https://profile.intra.42.fr/users/twang\a\e[34mtwang\e[34m\e]8;;\a ⭐\n\n"END);
}


int	main(int ac, char **av, char **env)
{
	char	*line;
	t_string_token	*str_tok_lst;
	(void)ac; (void)av;
	welcome_to_minihell();
	while (MINI_SHELL_MUST_GO_ON)
	{
		line = readline(PURPLE"Y a quoi ? "END);
		add_history(line);
		printf(BLUE"j'ai lu -> %s <-\n"END, line);
		get_lexed_str_token_lst_from_line(line, &str_tok_lst, env);
		// if (syntax_is_valid(str_tok_lst) == FAILURE)
		// {
		// 	string_token_destructor(str_tok_lst);
		// 	continue;
		// }
		display_str_token(str_tok_lst);
		execution(str_tok_lst);
	}
	return (0);
}

#endif