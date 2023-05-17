/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:35:32 by twang             #+#    #+#             */
/*   Updated: 2023/05/17 16:02:53 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---- prototypes ------------------------------------------------------------*/

static void			_change_color(char *prompt);
static const char	*_get_color_from_prompt(char *prompt);

/*----------------------------------------------------------------------------*/

char	*update_prompt(char *prompt)
{
	char	*end;

	_change_color(prompt);
	end = ft_strjoin_free_first_sf(ft_itoa(g_ret_val), " - Y a quoi : ");
	prompt[ft_strchr(prompt + 350, ':') - prompt + 2] = 0;
	end = ft_strjoin_free_sec_sf(prompt, end);
	return (end);
}

const char	*get_color(void)
{
	const char	*color_arr[] = {GREEN, RED, YELLOW, BLUE, RED};
	const int	ret_val_arr[] = {0, 1, 130, 131};
	size_t		index;

	index = 0;
	while (ret_val_arr[index] != g_ret_val && index < 4)
		index++;
	return (color_arr[index]);
}

static void	_change_color(char *prompt)
{
	char		*tmp;
	const char	*color_to;
	const char	*color_from;

	color_to = get_color();
	color_from = _get_color_from_prompt(prompt);
	if (color_from == NULL)
		return ;
	tmp = ft_strnstr(prompt, color_from, ft_strlen(prompt));
	while (tmp)
	{
		ft_memcpy(tmp, color_to, ft_strlen(color_to));
		tmp = ft_strnstr(prompt, color_from, ft_strlen(prompt));
	}
}

static const char	*_get_color_from_prompt(char *prompt)
{
	const char	*color_arr[] = {GREEN, RED, YELLOW, BLUE, RED};
	size_t		index;

	index = 0;
	while (index < 5)
	{
		if (ft_strnstr(prompt, (char *)color_arr[index], \
			ft_strlen(prompt)) != NULL)
			return (color_arr[index]);
		index++;
	}
	return (NULL);
}
