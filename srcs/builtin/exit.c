/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:15:52 by twang             #+#    #+#             */
/*   Updated: 2023/04/27 13:02:38 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

t_return_status	exit_builtin(char **av, t_data *data, char ***env_pt)
{
	(void)env_pt; (void)data;
	// int i;

	// if(data->cmds_block)
	// 	free_data(data);
	// i = 0;
	dprintf(2, RED"exit\n"END);
	// dprintf(2, RED"%s\n"END, av[2]);
	/*
	if (av[1])
	{
		dprintf(2, RED"minishell: exit: too many arguments\n"END);
		return (FAILURE);
	}
	g_ret_val = ft_atoi(av[1]);
	printf("%d\n", g_ret_val);
	// while (av[1][i])
	// {
	// 	if ((ft_isdigit(av[1][i]) != 1))
	// 	{
	// 		dprintf(2, RED"minishell: exit: %s: numeric argument required\n"END, av[1]);
	// 		break ;
	// 	}
	// 	i++;
	// }
	if (g_ret_val >= 255)
		exit(g_ret_val);*/
	exit(g_ret_val);
	/* parser le **av : - voir que les options sont correctes
			(-que une option -seulement des numeros -checker le overflow)*/
	/* que entre 0 et 255  >= 0 && <= 255  && if  > INT_MAX : je veux une valeure numerique  
		if >= 255 && <= INT_MAX : exit (nombre donne) il le prend, arrete le programme */
	/*nettoyer toute les allocations de memoires donnees*/
}