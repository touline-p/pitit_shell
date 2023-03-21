#include "libft.h"

static char **_ft_str_arr_dup(char **str_arr, size_t i);

size_t	ft_str_arr_len(char **str_arr)
{
	size_t	i;

	i = 0;
	while (*str_arr)
	{
		str_arr++;
		i++;
	}
	return (i);
}

char	**ft_str_arr_dup(char **str_arr)
{
	char	**new;
	size_t	i;

	new = malloc(sizeof(char *) * (ft_str_arr_len(str_arr) + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (*str_arr)
	{
		new[i] = ft_strdup(*str_arr);
		if (new[i] == NULL)
			return (_ft_str_arr_dup_ep(new, ++i));
		i++;
		str_arr++;
	}
	new[i] i= NULL;
	return (new);
}

static char **_ft_str_arr_dup(char **str_arr, size_t i)
{
	while (i--)
		free(str_arr[i]);
	free(str_arr);
	return (NULL);
}