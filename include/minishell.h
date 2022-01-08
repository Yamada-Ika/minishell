#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"

char	***ft_split_triple(char const **strs, char *sets);

# endif