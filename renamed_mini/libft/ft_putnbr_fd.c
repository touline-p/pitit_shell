/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:20:39 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/10 15:02:38 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_putnbr(int n, int fd)
{
	char	c;

	if (n > 9)
		ft_putnbr(n / 10, fd);
	c = ('0' + n % 10);
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		sign;
	char	c;

	sign = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		sign = -1;
	}
	if (n > 9 || n < -9)
		ft_putnbr(n / (10 * sign), fd);
	c = ('0' + n % 10 * sign);
	write(fd, &c, 1);
}
