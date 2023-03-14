
#include "libft.h"

t_ret_status	ft_join_str_arr_on(char **str_arr, char **line_pt)
{
	char	**arr_pin;
	char 	*str_pin;
	size_t	size_str;

	arr_pin = str_arr;
	size_str = 1;
	while (*arr_pin)
		size_str += ft_strlen(*(arr_pin++));
	*line_pt = malloc(size_str);
	if (*line_pt == NULL)
		return (MLC_ERR);
	str_pin = *line_pt;
	arr_pin = str_arr;
	while (*arr_pin)
		str_pin = ft_strcpy_rn(str_pin, *(arr_pin++));
	return (SUCCESS);
}