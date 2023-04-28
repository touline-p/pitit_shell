/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:15:52 by twang             #+#    #+#             */
/*   Updated: 2023/04/28 15:15:49 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

/*---- prototypes ------------------------------------------------------------*/

static void	check_exit_args(t_data *data, char **av);

/*----------------------------------------------------------------------------*/

t_return_status	exit_builtin(char **av, char ***env_pt, t_data *data)
{
	(void)env_pt;
	
	ft_dprintf(2, RED"exit\n"END);
	ft_dprintf(2, RED"%p\n"END, av[1]);
	if (av[1])
		check_exit_args(data, av);
	free_data(data);
	g_ret_val = 0;
	exit(g_ret_val);
	return (SUCCESS);
	/* parser le **av : - voir que les options sont correctes
			(-que une option -seulement des numeros -checker le overflow)*/
	/* que entre 0 et 255 >= 0 && <= 255  && if > INT_MAX : je veux une valeure numerique
		if >= 255 && <= INT_MAX : exit (nombre donne) il le prend, arrete le programme */
	/* nettoyer toute les allocations de memoires donnees */
}

static void	check_exit_args(t_data *data, char **av)
{
	int	i;

	i = 0;
	while (av[1][i])
	{
		if ((ft_isdigit(av[1][i]) != 1))
		{
			ft_dprintf(2, RED"minishell: exit: %s: numeric argument required\n"END, av[1]);
			g_ret_val = 2;
			free_data(data);
			exit(g_ret_val);
		}
		i++;
	}
	if (av[2])
		ft_dprintf(2, RED"minishell: exit: too many arguments\n"END);
	g_ret_val = ft_atoi(av[1]);
	if (g_ret_val >= 255)
	{
		free_data(data);
		exit(g_ret_val);
	}
}