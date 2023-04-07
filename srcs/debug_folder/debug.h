
#ifndef DEBUG_H
# define DEBUG_H

# define debug print_debug(__FILE__, __LINE__)
# define idebug(x) print_debug_int(x, __FILE__, __LINE__)
# define sdebug(x) print_debug_string(x, __FILE__, __LINE__)

# define END "\033[0m"
# define GREY "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"

# define END "\033[0m"
# define BOLD "\033[1m"
# define ITALIC "\033[3m"
# define UNDERLINE "\033[4m"
# define DEL_LINE "\033[2K\r"

#endif