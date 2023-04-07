#include "debug.h"
#include "stdio.h"

void    print_debug(char *file, int line)
{
    dprintf(2, PURPLE"%s:%d "END"this is debug message\n", file, line);
}

void    print_debug_string(char *value, char *file, int line)
{
    dprintf(2, PURPLE"%s:%d "END"%s\n", file, line, value);
}

void    print_debug_int(int value, char *file, int line)
{
    dprintf(2, PURPLE"%s:%d "END"%d\n", file, line, value);
}