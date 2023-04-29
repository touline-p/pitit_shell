/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:17:36 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/13 20:05:17 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "enums.h"

/*---- typedef structures ----------------------------------------------------*/

typedef struct s_list	t_list;

/*---- structures ------------------------------------------------------------*/

struct s_list
{
	void			*content;
	struct s_list	*next;
};


#endif