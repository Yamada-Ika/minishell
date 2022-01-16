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
//#include "../test/debug.h"
#include <stdbool.h>
#include <dirent.h>

char	***ft_split_triple(char const **strs, char *sets);

typedef enum e_token_kind
{
	TK_OP_DOUBLE_GR,	// ">>"
	TK_OP_SINGLE_LS,	// "<<"
	TK_OP_LS,			// "<"
	TK_OP_GR,			// ">"
 	TK_OP_PIPE,			// "|"
	TK_OP_DOLLAR,		// "$"
	TK_WORD,
	TK_WORD_IN_SINGLE_Q,		// "'"
	TK_WORD_IN_DOUBLE_Q,		// """
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
	bool			is_join_prev;
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
	// size_t			len;
	t_redirect_list	*next;
};

typedef struct s_command t_command;
struct s_command
{
	char			**word_list; // e.g. cat -option file_name
	t_redirect_list	*in_redir;
	t_redirect_list	*out_redir;
	t_redirect_list	*heredoc;
};

typedef struct s_node t_node;
struct s_node
{
	t_node_kind	kind;
	t_command	command;
	t_token		*word_list;
	size_t		word_list_size;
	t_node		*left;
	t_node		*right;
};

// utils.c
void error(char *str);
char	*here_doc(char *eos);
int		check_op(char *s);
size_t  get_word_len(char *p, t_token_kind kind, char *str);
size_t	get_valiable_name_len(char *str);
bool	is_redirect_kind(t_token_kind kind);

// parse.c
t_node	*command_line(t_token **tok);

// expansion.c
void	expansion(t_node *node);
char	*expand_str(char *str);

// sum_up_token_in_quote.c
void	sum_up_token_in_quote(t_node *node);

//handle_token_in_quotes.c
void	handle_token_in_quotes(t_token *token);

// void	create_t_command.c
void	create_t_command(t_node *node);

//tmp
int	main_(char *str);


//debug
void	debug_node(t_node *node);
void debug_tokenize(t_token *token);
void debug_token(t_token *token, size_t loop_cnt);
void	_debug_command(t_command cmd);

# endif
