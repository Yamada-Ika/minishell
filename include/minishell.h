#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"
#include <stdbool.h>
#include <dirent.h>

char	***ft_split_triple(char const **strs, char *sets);

typedef enum e_operation_kind
{
	OP_DOUBLE_GR,	// ">>"
	OP_SINGLE_LS,	// "<<"
	OP_LS,			// "<"
	OP_GR,			// ">"
 	OP_PIPE,		// "|"
	OP_SINGLE_Q,	// "'"
	OP_DOUBLE_Q,	// """
	OP_Dollar,		// "$"
} t_operation_kind;

typedef enum e_token_kind
{
	TK_OP,
	TK_WORD,
	TK_EOF,
} t_token_kind;

typedef struct s_token t_token;
struct s_token
{
	t_token_kind	kind;
	t_token			*next;
	t_token			*prev;
	char			*str;
	size_t			len;
};

t_token *tokenize(char *p);
void debug_tokenize(t_token *token);

typedef enum e_node_kind{
	ND_CMD, // command (e.g. cat)
	ND_PIPE, // "|"
} t_node_kind;

typedef struct s_redirect_list t_redirect_list;
struct s_redirect_list
{
	char			*word;
	char			*redirect;
	size_t			len;
	t_redirect_list	*next;
};

typedef struct s_command t_command;
struct s_command
{
	char			**word_list; // e.g. cat -option file_name
	t_redirect_list	*in_redir;
	t_redirect_list	*out_redir;
};

typedef struct s_node t_node;
struct s_node
{
	t_node_kind	kind;
	t_command	*command;
	t_token		*word_list;
	size_t		word_list_size;
	t_node		*left;
	t_node		*right;
};

// utils.c
void error(char *str);
char	*here_doc(char *eos);
int	check_op(t_token *tok);

// parse.c
t_node	*command_line(t_token **tok);

// expansion.c
void	expansion(t_node *node);

# endif