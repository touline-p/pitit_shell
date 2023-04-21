
#include "minishell_parsing.h"
#include "minishell_execution.h"
#include "structures_execution.h"
#include <readline/readline.h>

#include "../incs/execution_incs/minishell_execution.h"
#include "../incs/parsing_incs/minishell_parsing.h"
/*---- prototypes ------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
int g_ret_val;
#define MAIN
#ifdef MAIN
static t_return_status welcome_to_minihell(char ***env_pt)
{
	g_ret_val = 0;
	if (env_init_on(env_pt) != SUCCESS)
		return (FAILED_MALLOC);
	ft_dprintf(2, PURPLE"\n------------------------------------------------------------------------------\t\n"END);
	printf(PURPLE" __    __   __   __   __   __   ______   __  __   ______   __       __        \n");
	printf("/\\ \"-./  \\ /\\ \\ /\\ \"-.\\ \\ /\\ \\ /\\  ___\\ /\\ \\_\\ \\ /\\  ___\\ /\\ \\     /\\ \\       \n");
	printf("\\ \\ \\-./\\ \\\\ \\ \\\\ \\ \\-.  \\\\ \\ \\\\ \\___  \\\\ \\  __ \\\\ \\  __\\ \\ \\ \\____\\ \\ \\____  \n");
	printf(" \\ \\_\\ \\ \\_\\\\ \\_\\\\ \\_\\\\\"\\_\\\\ \\_\\\\/\\_____\\\\ \\_\\ \\_\\\\ \\_____\\\\ \\_____\\\\ \\_____\\ \n");
	printf("  \\/_/  \\/_/ \\/_/ \\/_/ \\/_/ \\/_/ \\/_____/ \\/_/\\/_/ \\/_____/ \\/_____/ \\/_____/ \n");
	ft_dprintf(2, PURPLE" \n------------------------------------------------------------------------------\t\n"END);
	ft_dprintf(2, ITALIC PURPLE"\t\t\t\t\t\t by ⭐ \e]8;;https://profile.intra.42.fr/users/bpoumeau\a\e[34mbpoumeau\e[34m\e]8;;\a ");
	ft_dprintf(2, "& \e]8;;https://profile.intra.42.fr/users/twang\a\e[34mtwang\e[34m\e]8;;\a ⭐\n\n"END);
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_sig
	char	*line;
	t_string_token	*str_tok_lst;
	(void)ac; (void)av;
	if (welcome_to_minihell(&env) != SUCCESS)
		return (1);
	while (MINI_SHELL_MUST_GO_ON)
	{
		line = readline("Y a quoi ? ");
		if (line == NULL || ft_str_is_ascii(line) == false) {
			printf("\n");
			free(line);
			continue;
		}
		if (ft_strncmp("END", line, 4) == 0)
			return (clear_history(), free(line), 0);
		add_history(line);
		// printf(BLUE"j'ai lu ->%s<-\n"END, line);
		get_lexed_str_token_lst_from_line(line, &str_tok_lst, env);
		if (syntax_is_valid(str_tok_lst) == FAILURE)
			// || cut_all_lines(str_tok_lst) != SUCCESS
			// || join_all_lines(str_tok_lst, env) != SUCCESS)
		{
		 	string_token_destructor(str_tok_lst);
		 	continue;
		}
		del_space_token(str_tok_lst);
		execution(str_tok_lst, &env);
	}
	return (0);
}

#endif
