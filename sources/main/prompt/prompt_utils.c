/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:06:10 by twang             #+#    #+#             */
/*   Updated: 2023/05/19 12:17:54 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_all_box(char *box, char *pwd, size_t box_width)
{
	size_t	i;

	i = 0;
	box = ft_strcpy_rn(box, get_color());
	box = ft_strcpy_rn(box, "\001\u2554");
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
}

t_return_status	clean_the_prompt(char *prompt, char *line, char **env)
{
	free(line);
	free(prompt);
	ft_free_split(env);
	clear_history();
	//ft_dprintf(1, RED"exit\n"END);
	exit(0);
	return (SUCCESS);
}
