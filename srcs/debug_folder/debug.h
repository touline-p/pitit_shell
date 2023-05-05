
#ifndef DEBUG_H
# define DEBUG_H

# define debug print_debug(__FILE__, __LINE__)
# define idebug(x) print_debug_int(x, __FILE__, __LINE__)
# define sdebug(x) print_debug_string(x, __FILE__, __LINE__)

void    print_debug(char *file, int line);
void    print_debug_string(char *value, char *file, int line);
void    print_debug_int(int value, char *file, int line);

# define END "\001\033[0m\002"
# define GREY "\001\033[1;30m\002"
# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[1;34m\002"
# define PURPLE "\001\033[1;35m\002"

# define END "\001\033[0m\002"
# define BOLD "\001\033[1m\002"
# define ITALIC "\001\033[3m\002"
# define UNDERLINE "\001\033[4m\002"
# define DEL_LINE "\001\033[2K\r\002"
# include "minishell_execution.h"



#endif