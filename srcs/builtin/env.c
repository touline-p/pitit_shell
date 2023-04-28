/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:58:14 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/04/28 15:20:25 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

t_return_status	env_builtin(char **av, char ***env_pt, t_data *data)
{
	(void)data;
	char	**pin;

	ft_free_split(av);
	pin = *env_pt;
	while (*pin)
	{
		printf("%s\n", *pin);
		pin++;
	}
	return (SUCCESS);
}
