/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:58:14 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/04/26 22:58:15 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

t_return_status	env_builtin(char **av, char ***env_pt)
{
	char	**pin;

	(void)av;
	pin = *env_pt;
	while (*pin)
	{
		if (ft_strchr(*pin, '='))
			printf("%s\n", *pin);
		pin++;
	}
	g_ret_val = 0;
	return (SUCCESS);
}
