/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dquotes_str_by_env_value.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:23:23 by twang             #+#    #+#             */
/*   Updated: 2023/05/16 18:23:51 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

void	replace_minus_by_space(unsigned int nb, char *content)
{
	(void) nb;
	if (*content == - ' ')
		*content = ' ';
	content++;
}

t_return_status	replace_dquotes_str_by_env_value(char **line_pt, char **env)
{
	char	**str_arr;

	ft_striteri(*line_pt, &cpy_next_char);
	if (cut_line_on(*line_pt, &str_arr) != SUCCESS
		|| join_arr_on(str_arr, line_pt, env) != SUCCESS)
		return (FAILED_MALLOC);
	ft_striteri(*line_pt, &replace_minus_by_space);
	return (SUCCESS);
}
