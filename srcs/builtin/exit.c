/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:15:52 by twang             #+#    #+#             */
/*   Updated: 2023/05/03 11:04:15 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static t_return_status	check_exit_args(char **av, char ***env_pt);

/*----------------------------------------------------------------------------*/

t_return_status	exit_builtin(char **av, char ***env_pt)
{

	ft_dprintf(2, RED"exit\n"END);
	if (av[1])
	{
		if (check_exit_args(av, env_pt) != SUCCESS)
			return (FAILURE);
	}

	ft_free_split(*env_pt);
	g_ret_val = 0;
	ft_free_split(av);
	exit(g_ret_val);
	return (SUCCESS);
}

static t_return_status	check_exit_args(char **av, char ***env_pt)
{
	if (ft_isnbr(av[1]) == false)
	{
		ft_dprintf(2, RED"minishell: exit: %s: numeric argument required\n"END, av[1]);
		g_ret_val = 2;
		ft_free_split(av);
		ft_free_split(*env_pt);
		exit(g_ret_val);
	}
	if (ft_str_array_len(av) > 2)
	{
		ft_dprintf(2, RED"minishell: exit: too many arguments\n"END);
		g_ret_val = 1;
		ft_free_split(av);
		return (FAILURE);
	}
	g_ret_val = ft_atoi(av[1]);
	ft_free_split(av);
	ft_free_split(*env_pt);
	exit(g_ret_val);
	return (SUCCESS);
}