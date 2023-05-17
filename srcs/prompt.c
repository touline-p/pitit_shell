/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:47:45 by twang             #+#    #+#             */
/*   Updated: 2023/05/16 17:53:41 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"
#include "minishell_parsing.h"
#include "../incs/execution_incs/minishell_execution.h"
#include "../incs/parsing_incs/minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	_get_alloc_box_on(char **box_pt, char **env);
static t_return_status	_get_alloc_line_prompt_on(char **line_pt, char **env);

/*----------------------------------------------------------------------------*/

t_return_status	get_prompt_on(char **prompt_pt, char **env)
{
	char	*line;
	char	*box;

	box = NULL;
	line = NULL;
	free(*prompt_pt);
	*prompt_pt = NULL;
	if (_get_alloc_box_on(&box, env) != SUCCESS
		|| box == NULL
		|| _get_alloc_line_prompt_on(&line, env) != SUCCESS)
		return (free(box), free(line), SUCCESS);
	*prompt_pt = ft_strjoin(box, line);
	free(box);
	free(line);
	get_prompt(*prompt_pt, 1);
	return (SUCCESS);
}

const char	*get_color(void);

static char *_get_box(void)
{
	const char	*color_arr[] = {GREEN"\001\u2554", RED"\001\u2554", \
							YELLOW"\001\u2554", BLUE"\001\u2554", }
	const int	ret_val_arr[] = {0, 1, 130, 131};
	size_t		index;

	index = 0;
	while (ret_val_arr[index] != g_ret_val && index < 5)
		index++;
	return ((char *)color_arr[index]);
}


static t_return_status	_get_alloc_box_on(char **box_pt, char **env)
{
	char	*box;
	char	*pwd;
	size_t	box_width;
	size_t	i;

	pwd = get_env_content_from_key("PWD", env);
	if (pwd == NULL)
		pwd = "We are kinda lost bitches.";
	box_width = (ft_strlen(pwd) + 4);
	box = malloc(ft_strlen(GREEN) + (box_width * 4 + 2) * \
					ft_strlen("\001\u2550\002") + box_width \
					+ 4 + ft_strlen("\001\u255D\002\n"END));
	if (box == NULL)
		return (perror("prompt"), FAILED_MALLOC);
	*box_pt = box;
	if (g_ret_val == 0)
		box = ft_strcpy_rn(box, GREEN"\001\u2554");
	else if (g_ret_val == 130)
		box = ft_strcpy_rn(box, YELLOW"\001\u2554");
	else if (g_ret_val == 131)
		box = ft_strcpy_rn(box, BLUE"\001\u2554");
	else
		box = ft_strcpy_rn(box, RED"\001\u2554");
	i = 0;
	while (i < box_width)
	{
		box = ft_strcpy_rn(box, "\u2550");
		i++;
	}
	box = ft_strcpy_rn(box, "\u2557\n");
	box = ft_strcpy_rn(box, "\u2551  ");
	box = ft_strcpy_rn(box, pwd);
	box = ft_strcpy_rn(box, "  \u2551\n");
	box = ft_strcpy_rn(box, "\u255A");
	i = 0;
	while (i < box_width)
	{
		box = ft_strcpy_rn(box, "\u2550");
		i++;
	}
	box = ft_strcpy_rn(box, "\u255D\002\n"END);
	*box = 0;
	return (SUCCESS);
}

static t_return_status	_get_alloc_line_prompt_on(char **line_pt, char **env)
{
	char	*line;
	char	*shlvl;
	char	*g_ret_str;

	shlvl = get_env_content_from_key("SHLVL", env);
	if (shlvl == NULL)
		shlvl = "At least THREE THOUSANDS";
	g_ret_str = ft_itoa(g_ret_val);
	if (g_ret_str == NULL)
		return (FAILED_MALLOC);
	line = malloc(ft_strlen(g_ret_str) + ft_strlen(shlvl) + \
					ft_strlen(PROMPT_MESSAGE) + 4);
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
