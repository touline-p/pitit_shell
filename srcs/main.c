
#include "minishell_parsing.h"
#include "minishell_execution.h"
#include "structures_execution.h"
#include <readline/readline.h>

#include "../incs/execution_incs/minishell_execution.h"
#include "../incs/parsing_incs/minishell_parsing.h"
/*---- global definition -----------------------------------------------------*/

int g_ret_val;

/*----------------------------------------------------------------------------*/

#define MAIN
#ifdef MAIN
/*---- prototypes ------------------------------------------------------------*/

static t_return_status welcome_to_minihell(char ***env_pt);

/*----------------------------------------------------------------------------*/


int	main(int ac, char **av, char **env)
{
	(void)ac; (void)av;
	char	*line;
	t_data	data;
	t_string_token	*str_tok_lst;

	if (welcome_to_minihell(&env) != SUCCESS)
		return (1);
	while (MINI_SHELL_MUST_GO_ON)
	{
		/* ---- test it like it's hot ------------
		init_signals();
		display_info(env);
		----------------------------------------- */
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_signal_main);
		printf(GREEN"%s "END, get_env_content_from_key("SHLVL", env));
		printf(END":");	
		printf(RED" %d"END, g_ret_val);
		line = readline(" - Y a quoi ? ");
		if (line == NULL || ft_str_is_ascii(line) == false)
		{
			free(line);
			g_ret_val = 0;
			exit(g_ret_val);
		}
		else if (ft_strncmp("END", line, 4) == 0)
			return (clear_history(), free(line), 0);
		add_history(line);
		if (line != NULL)
		{
			get_lexed_str_token_lst_from_line(line, &str_tok_lst, env);
			if (str_tok_lst == NULL || syntax_is_valid(str_tok_lst) == FAILURE)
			{
				string_token_destructor(str_tok_lst);
				continue;
			}
			del_space_token(str_tok_lst);
			execution(&data, str_tok_lst, &env);
			free(data.cmds_block);
			string_token_destructor(str_tok_lst);
		}
		
	}
	return (0);
}

static t_return_status welcome_to_minihell(char ***env_pt)
{
	g_ret_val = 0;
	if (env_init_on(env_pt) != SUCCESS)
		return (FAILED_MALLOC);
	ft_dprintf(2, PURPLE"\n--------------------------------------------------");
	ft_dprintf(2, "----------------------------\t\n"END);
	ft_dprintf(2, PURPLE" __    __   __   __   __   __   ______   __  __   ______   __       __        \n");
	ft_dprintf(2, "/\\ \"-./  \\ /\\ \\ /\\ \"-.\\ \\ /\\ \\ /\\  ___\\ /\\ \\_\\ \\ /\\  ___\\ /\\ \\     /\\ \\       \n");
	ft_dprintf(2, "\\ \\ \\-./\\ \\\\ \\ \\\\ \\ \\-.  \\\\ \\ \\\\ \\___  \\\\ \\  __ \\\\ \\  __\\ \\ \\ \\____\\ \\ \\____  \n");
	ft_dprintf(2, " \\ \\_\\ \\ \\_\\\\ \\_\\\\ \\_\\\\\"\\_\\\\ \\_\\\\/\\_____\\\\ \\_\\ \\_\\\\ \\_____\\\\ \\_____\\\\ \\_____\\ \n");
	ft_dprintf(2, "  \\/_/  \\/_/ \\/_/ \\/_/ \\/_/ \\/_/ \\/_____/ \\/_/\\/_/ \\/_____/ \\/_____/ \\/_____/ \n");
	ft_dprintf(2, PURPLE"\n--------------------------------------------------");
	ft_dprintf(2, "----------------------------\t\n"END);
	ft_dprintf(2, ITALIC PURPLE"\t\t\t\t\t\t by ⭐ \e]8;;https://profile.intra.42.fr/users/bpoumeau\a\e[34mbpoumeau\e[34m\e]8;;\a ");
	ft_dprintf(2, "& \e]8;;https://profile.intra.42.fr/users/twang\a\e[34mtwang\e[34m\e]8;;\a ⭐\n\n"END);
	return (SUCCESS);
}

/* ---- test it like it's hot -------------

static t_return_status welcome_to_minihell(char ***env_pt)
{
	g_ret_val = 0;
	if (env_init_on(env_pt) != SUCCESS)
		return (FAILED_MALLOC);
	printf(PURPLE"\n--------------------------------------------------");
	printf("----------------------------\t\n"END);
	printf(PURPLE" __    __   __   __   __   __   ______   __  __   __");
	printf("____   __       __        \n");
	printf("/\\ \"-./  \\ /\\ \\ /\\ \"-.\\ \\ /\\ \\ /\\  ___\\ /\\ \ ");
	printf("\_\\ \\ /\\  ___\\ /\\ \\     /\\ \\       \n");
	printf("\\ \\ \\-./\\ \\\\ \\ \\\\ \\ \\-.  \\\\ \\ \\\\ \\___  \\");
	printf("\\ \\  __ \\\\ \\  __\\ \\ \\ \\____\\ \\ \\____  \n");
	printf(" \\ \\_\\ \\ \\_\\\\ \\_\\\\ \\_\\\\\"\\_\\\\ \\_\\\\/\\__");
	printf("___\\\\ \\_\\ \\_\\\\ \\_____\\\\ \\_____\\\\ \\_____\\ \n");
	printf("  \\/_/  \\/_/ \\/_/ \\/_/ \\/_/ \\/_/ \\/_____/ \\/_/\\/_");
	printf("/ \\/_____/ \\/_____/ \\/_____/ \n");
	printf(PURPLE"\n--------------------------------------------------");
	printf("----------------------------\t\n"END);
	printf(ITALIC PURPLE"\t\t\t\t\t\t by ⭐ \e]8;;https://profile.intra.42.fr/users/bpoumeau\a\e[34mbpoumeau\e[34m\e]8;;\a ");
	printf("& \e]8;;https://profile.intra.42.fr/users/twang\a\e[34mtwang\e[34m\e]8;;\a ⭐\n\n"END);
	return (SUCCESS);
}

static void display_info(char ***env_pt)
{
	ft_dprintf(2, GRAY"%s "END, get_env_content_from_key("PWD", env));
	ft_dprintf(2, GREEN"%s "END, get_env_content_from_key("SHLVL", env));
	ft_dprintf(2, END":");	
	ft_dprintf(2, RED" %d"END, g_ret_val);
}

----------------------------------------- */

#endif
