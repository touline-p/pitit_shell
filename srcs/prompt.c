/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 23:50:14 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/14 00:48:55 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

t_return_status welcome_to_minihell(char ***env_pt)
{
	g_ret_val = 0;
	if (env_init_on(env_pt) != SUCCESS)
		return (FAILED_MALLOC);
	ft_dprintf(2, PURPLE"%s%s", START_MSG_00, START_MSG_01);
	ft_dprintf(2, "%s%s", START_MSG_02, START_MSG_03);
	ft_dprintf(2, "%s%s", START_MSG_04, START_MSG_05);
	ft_dprintf(2, "%s%s%s", START_MSG_06, START_MSG_07, START_MSG_08);
	ft_dprintf(2, "%s%s%s", START_MSG_09, START_MSG_10, START_MSG_11);
	ft_dprintf(2, "%s%s", START_MSG_12, START_MSG_13);
	ft_dprintf(2, "%s%s", START_MSG_00, START_MSG_01);
	ft_dprintf(2, ITALIC"%s"END, START_MSG_14);
	return (SUCCESS);
}

t_return_status	get_prompt_on(char **prompt_pt, char **env)
{
	char	*line;
	char	*box;

	box = NULL;
	line = NULL;
	free(*prompt_pt);
	*prompt_pt = NULL;
	if (get_allocated_box_on(&box, env) != SUCCESS
		|| box == NULL
		|| get_allocated_line_prompt_on(&line, env) != SUCCESS)
		return (free(box), free(line), SUCCESS);
	*prompt_pt = ft_strjoin(box, line);
	free(box);
	free(line);
	return (SUCCESS);
}

static t_return_status get_allocated_box_on(char **box_pt, char **env)
{
	char	*box;
	char	*pwd;
	size_t	box_width;
	size_t	i;

	pwd = get_env_content_from_key("PWD", env);
	if (pwd == NULL)
		pwd = "We are kinda lost bitches.";
	box_width = (ft_strlen(pwd) + 4);
	box = malloc(ft_strlen(GREEN) + (box_width * 4 + 2) * ft_strlen("\001\u2550\002") + box_width + 4 + ft_strlen( "\001\u255D\002\n"END));
	if (box == NULL)
		return (perror("prompt"), FAILED_MALLOC);
	*box_pt = box;
	if (g_ret_val == 0)
		box = ft_strcpy_rn(box, GREEN"\001\u2554");
	else if (g_ret_val == 130 || g_ret_val == 131)
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

static t_return_status get_allocated_line_prompt_on(char **line_pt, char **env)
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