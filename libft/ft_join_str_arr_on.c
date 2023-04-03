
#include "libft.h"

t_return_status	ft_join_str_arr_on(char **str_arr, char **line_pt)
{
	char	**arr_pin;
	char 	*str_pin;
	size_t	size_str;

	arr_pin = str_arr;
	size_str = 1;
	while (*arr_pin)
		size_str += ft_strlen(*(arr_pin++));
	*line_pt = malloc(size_str);
	printf("%p\n", *line_pt);
	if (*line_pt == NULL)
		return (FAILED_MALLOC);
	str_pin = *line_pt;
	arr_pin = str_arr;
	while (*arr_pin)
		str_pin = ft_strcpy_rn(str_pin, *(arr_pin++));
	return (SUCCESS);
}

/*
int main()
{
	char **oh = ft_split("", ' ');
	char *line;
	ft_join_str_arr_on(oh, &line);
	printf("-%s-\n", line);
}
 */
