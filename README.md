<h3 align="center">
LE PITIT_SHELL
</h3>

---

<h3 align="center">
Aussi mignon qu’un vrai shell!
</h3>
</p>

<h3 align="center">
	<a href="#%EF%B8%8F-about">About</a>
	<span> · </span>
	<a href="#-index">Index</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
	<span> · </span>
	<a href="#-useful-links">Useful Links</a>
</h3>

---

## About
</p>
<h3 align="center">
This project is focused on creating a minimalistic shell, which is a program that allows users to interact with their operating system by typing commands. By participating in this project, individuals can learn how to create a functional and efficient shell that performs tasks such as running programs, managing input and output, and handling errors.

You can find more detailed information on the project in the [subject](./minishell_subject.pdf).
</h3>

## Index

< infile cat -e | cat | cat > outfile

data->cmds_block[0]->command = "cat" "-e"
data->cmds_block[0]->infile = fd_in
data->cmds_block[0]->outfile = -1
data->cmds_block[0]->pipes[2] = ignore

data->cmds_block[1]->command = "cat"
data->cmds_block[1]->infile = -1
data->cmds_block[1]->outfile = -1
data->cmds_block[1]->pipes[2] = ignore

data->cmds_block[2]->command = "cat"
data->cmds_block[2]->infile = -1
data->cmds_block[2]->outfile = fd_out
data->cmds_block[2]->pipes[2] = ignore

check lst_tokens
check chevrons		-> infile / here_doc 
					-> expand to here_doc
					-> outfile / append
check commands 		-> recup commandes + args
					-> add path
					-> check fds -> standart -> pipes ...
					-> builtins -> call built_in function
					-> exec command

## Usage
### Instructions

**1. Compiling the program**

To compile the program, run:

```shell
$ make
```

**2. Executing the program**

To execute the program, run:

```shell
$ ./minishell
```

## Useful Links
* [42 Docs - minishell](https://harm-smits.github.io/42docs/projects/minishell)
* [Useful notes on Shell & Shell Scripting](https://www.notion.so/Shell-Shell-Scripting-6e0f0290a0304dad93a1d25ba15d92fe)
* [Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html)
* [The Open Group Base Specifications - Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
* [Introduction to Systems Programming: a Hands-on Approach - Chapter 5. Writing Your Own Shell ](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

by [bpoumeau](https://profile.intra.42.fr/users/bpoumeau) & [twang](https://profile.intra.42.fr/users/twang).