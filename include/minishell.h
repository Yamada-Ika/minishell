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
#include <stdbool.h>

char	***ft_split_triple(char const **strs, char *sets);

typedef enum e_token_kind{
	TK_OP = 0,
	TK_WORD,
	TK_EOF,
} t_token_kind;

typedef struct s_token t_token;
struct s_token {
	t_token_kind	kind;
	t_token			*next;
	char			*str;
	size_t			len;
};

t_token *tokenize(char *p);
void debug_tokenize(t_token *token);

// utils.c
void error(char *str);
char	*here_doc(char *eos);

# endif