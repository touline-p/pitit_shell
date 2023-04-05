//
// Created by bpoumeau on 4/4/23.
//

#include "libft.h"

char	*ft_strstr(char *big, char *little)
{
	size_t	little_size;

	while (*big)
	{
		if (ft_strncmp(big, little, ft_strlen(little)))
			return (big);
		big++;
	}
	return (NULL);
}

#ifdef TST_STRSTR



#endif