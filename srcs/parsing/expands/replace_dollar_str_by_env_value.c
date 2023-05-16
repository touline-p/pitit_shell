/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_str_by_env_value.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:05:15 by twang             #+#    #+#             */
/*   Updated: 2023/05/16 18:06:00 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

void	replace_space_by_minus(unsigned int nb, char *content)
{
	(void) nb;
	if (*content == ' ')
		*content = - ' ';
	content++;
}

static t_return_status	_expand_the_g_ret_val(char **pin_pt)
{
	free(*pin_pt);
	*pin_pt = ft_itoa(g_ret_val);
	if (*pin_pt == NULL)
		return (FAILURE);
	return (SUCCESS);
}

t_return_status	replace_dollar_str_by_env_value(char **pin_pt, char **env)
{
	char	*content;

	if (ft_strlen(*pin_pt) == 1)
		return (SUCCESS);
	if (ft_strcmp(*pin_pt, "$?") == 0)
		return (_expand_the_g_ret_val(pin_pt));
	content = get_env_content_from_key(*pin_pt + 1, env);
	free(*pin_pt);
	if (content == NULL)
		*pin_pt = ft_strdup("");
	else
		*pin_pt = ft_strdup(content);
	if (*pin_pt == NULL)
		return (FAILED_MALLOC);
	ft_striteri(*pin_pt, &replace_space_by_minus);
	return (SUCCESS);
}
