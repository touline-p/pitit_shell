#include "debug.h"
#include "stdio.h"
#include "minishell_execution.h"
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

void    print_builtin(t_builtin built)
{
    const char	*name_arr[] = {NULL, "env","echo", "export", \
							"exit", "unset", "cd", "pwd", "empty", "subshell"};
    dprintf(2, "\nbuiltin is %s\n", name_arr[built]);
}

void    print_is_heredoc(bool is)
{
    if (is)
        dprintf(2,"has heredoc\n");
    else
        dprintf(2,"hasn't heredoc\n");
}

void    print_fd(char *msg, int fd)
{
    dprintf(2,"%s fd_hd is %d\n", msg, fd);
}

void    print_pid(int pid)
{
    dprintf(2, "the pid is %d\n\n", pid);
}

void    print_cmd_block(char *msg, t_cmd cmd)
{
		if (*msg == '1')
			usleep(5000);
	dprintf(2, "\n\nname : %s\n", msg);
    print_builtin(cmd.id_command);
    ft_eprint_split(cmd.commands);
    print_is_heredoc(cmd.is_heredoc);
    print_fd("infile",cmd.infile);
    print_fd("outfile",cmd.outfile);
	print_fd("fd[0]",cmd.fd_hd[0]);
	print_fd("fd[1]",cmd.fd_hd[1]);
	if (cmd.is_ambiguous == true)
		ft_dprintf(2, "it s ambiguous\n");
	else
		ft_dprintf(2, "it s goood\n");
    print_pid(cmd.process_id);
}

