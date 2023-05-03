
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

static t_return_status	welcome_to_minihell(char ***env_pt);
static t_return_status get_allocated_line_prompt_on(char **line_pt, char **env);
static t_return_status get_allocated_box_on(char **box_pt, char **env);

/*----------------------------------------------------------------------------*/


t_return_status	_get_prompt_on(char **prompt_pt, char **env)
{
	char	*prompt;
	char	*line;
	char	*box;

	if (*prompt_pt != NULL)
		free(*prompt_pt);
	*prompt_pt = NULL;
	box = NULL;
	line = NULL;
	if (get_allocated_box_on(&box, env) != SUCCESS
		|| box == NULL
		|| get_allocated_line_prompt_on(&line, env) != SUCCESS)
		return (free(box), free(line), SUCCESS);
	prompt = ft_strjoin(box, line);
	free(box);
	free(line);
	*prompt_pt = prompt;
	return (SUCCESS);
}



int	main(int ac, char **av, char **env)
{
	(void)ac; (void)av;
	char	*line;
	t_data	data;
	t_string_token	*str_tok_lst;
	char	*prompt;

	prompt = NULL;
	line = NULL;
	str_tok_lst = NULL;
	if (welcome_to_minihell(&env) != SUCCESS)
		return (1);
	while (MINI_SHELL_MUST_GO_ON)
	{
		init_signals();
		_get_prompt_on(&prompt, env);
		if (g_ret_val == 131)
			ft_dprintf(2, RED"Quit (core dumped)\n"END);
		if (g_ret_val == 130)
			dprintf(2, "\n");
		line = readline(prompt);
		if (line == NULL || ft_str_is_ascii(line) == false)
		{
			free(line);
			// if (data.cmds_block)
			// 	free(data.cmds_block);
			ft_dprintf(2, RED"exit\n"END);
			exit(0);
		}
		if (ft_strncmp("END", line, 4) == 0)
			return (clear_history(), free(line), 0);
		add_history(line);
		if (get_lexed_str_token_lst_from_line(line, &str_tok_lst, env) != SUCCESS)
			continue ;
		if (syntax_is_valid(str_tok_lst) != SUCCESS)
		{
		 	string_token_destructor(str_tok_lst);
		 	continue;
		}
		del_space_token(str_tok_lst);
		execution(&data, str_tok_lst, &env);
		if (data.cmds_block)
			free(data.cmds_block);
		string_token_destructor(str_tok_lst);
	}
	return (0);
}

static t_return_status welcome_to_minihell(char ***env_pt)
{
	g_ret_val = 0;
	if (env_init_on(env_pt) != SUCCESS)
		return (FAILED_MALLOC);
	ft_dprintf(2, PURPLE"\n------------------------------------------------------------------------------\t\n"END);
	ft_dprintf(2, PURPLE" __    __   __   __   __   __   ______   __  __   ______   __       __        \n");
	ft_dprintf(2, "/\\ \"-./  \\ /\\ \\ /\\ \"-.\\ \\ /\\ \\ /\\  ___\\ /\\ \\_\\ \\ /\\  ___\\ /\\ \\     /\\ \\       \n");
	ft_dprintf(2, "\\ \\ \\-./\\ \\\\ \\ \\\\ \\ \\-.  \\\\ \\ \\\\ \\___  \\\\ \\  __ \\\\ \\  __\\ \\ \\ \\____\\ \\ \\____  \n");
	ft_dprintf(2, " \\ \\_\\ \\ \\_\\\\ \\_\\\\ \\_\\\\\"\\_\\\\ \\_\\\\/\\_____\\\\ \\_\\ \\_\\\\ \\_____\\\\ \\_____\\\\ \\_____\\ \n");
	ft_dprintf(2, "  \\/_/  \\/_/ \\/_/ \\/_/ \\/_/ \\/_/ \\/_____/ \\/_/\\/_/ \\/_____/ \\/_____/ \\/_____/ \n");
	ft_dprintf(2, PURPLE" \n------------------------------------------------------------------------------\t\n"END);
	ft_dprintf(2, ITALIC PURPLE"\t\t\t\t\t\t by ⭐ \e]8;;https://profile.intra.42.fr/users/bpoumeau\a\e[34mbpoumeau\e[34m\e]8;;\a ");
	ft_dprintf(2, "& \e]8;;https://profile.intra.42.fr/users/twang\a\e[34mtwang\e[34m\e]8;;\a ⭐\n\n"END);
	return (SUCCESS);
}
static t_return_status get_allocated_box_on(char **box_pt, char **env)
{
	char	*box;
	char	*pwd;
	size_t	box_width;
	size_t		i;

	pwd = get_env_content_from_key("PWD", env);
	if (pwd == NULL)
		pwd = "We are kinda lost bitches.";
	box_width = (ft_strlen(pwd) + 4);
	box = malloc(ft_strlen(GREEN) + (box_width * 4 + 2) * ft_strlen("\001\u2550\002") + box_width + 4 + ft_strlen( "\001\u255D\002\n"END));
	if (box == NULL)
		return (perror("prompt"), FAILED_MALLOC);
	*box_pt = box;

	box = ft_strcpy_rn(box, GREEN"\001\u2554\002");
	i = 0;
	while (i < box_width)
	{
		box = ft_strcpy_rn(box, "\001\u2550\002");
		i++;
	}
	box = ft_strcpy_rn(box, "\001\u2557\002\n");
	box = ft_strcpy_rn(box, "\001\u2551\002  ");
	box = ft_strcpy_rn(box, pwd);
	box = ft_strcpy_rn(box, "  \001\u2551\002\n");
    box = ft_strcpy_rn(box, "\001\u255A\002");
	i = 0;
	while (i < box_width)
	{
		box = ft_strcpy_rn(box, "\001\u2550\002");
		i++;
	}
	box = ft_strcpy_rn(box, "\001\u255D\002\n"END);
	*box = 0;
	return (SUCCESS);
}
#define PROMPT_MESSAGE " - Balance mon bon Bro : "
static t_return_status get_allocated_line_prompt_on(char **line_pt, char **env)
{
	char	*line;
	char	*shlvl;
	char	*g_ret_str;

	shlvl = get_env_content_from_key("SHLVL", env);
	if (shlvl == NULL)
		shlvl = "At least THREE THOUSANDS : ";
	g_ret_str = ft_itoa(g_ret_val);
	if (g_ret_str == NULL)
		return (FAILED_MALLOC);
	line = malloc(ft_strlen(g_ret_str) + ft_strlen(shlvl) + ft_strlen(PROMPT_MESSAGE) + 4);
	if (line == NULL)
		return (free(g_ret_str), FAILED_MALLOC);
	*line_pt = line;
	line = ft_strcpy_rn(line, shlvl);
	line = ft_strcpy_rn(line, " : ");
	line = ft_strcpy_rn(line, g_ret_str);
	line = ft_strcpy_rn(line, PROMPT_MESSAGE);
	free(g_ret_str);
	return (SUCCESS);
}
#endif
