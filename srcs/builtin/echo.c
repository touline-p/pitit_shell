/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:58:08 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/04/28 15:20:06 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static	bool	_is_option_n(char *arg);

t_return_status	echo_builtin(char **av, char ***env_pt, t_data *data)
{
	char	**tmp;
	bool	option;

	(void)data;
	(void)env_pt;
	tmp = av + 1;
	option = _is_option_n(*tmp);
	if (option == true)
		tmp++;
	if (*tmp)
	{
		printf("%s", *tmp);
		tmp++;
	}
	while (*tmp)
	{
		printf(" %s", *tmp);
		tmp++;
	}
	if (option == false)
		printf("\n");
	ft_free_split(av);
	return (SUCCESS);
}

static bool	_is_option_n(char *arg)
{
	if (arg == NULL || *(arg) != '-' || *(arg + 1) != 'n')
		return (false);
	arg++;
	while (*arg == 'n')
		arg++;
	if (*arg)
		return (false);
	return (true);
}
