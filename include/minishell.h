#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
//#include "../test/debug.h"
# include <stdbool.h>
# include <dirent.h>

// env
# include "envvar.h"

# define ERROR -1
# define INIT_ERRNO 0

char	***ft_split_triple(char const **strs, char *sets);

typedef enum e_token_kind
{
	EMPTY = -1,
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
}	t_token_kind;

typedef struct s_token	t_token;
struct s_token
{
	t_token_kind	kind;
	t_token			*next;
	t_token			*prev;
	char			*str;
	size_t			len;
	bool			is_join_prev;
};

t_token	*tokenize(char *p);
void	debug_tokenize(t_token *token);

typedef enum e_node_kind{
	ND_CMD, // command (e.g. cat)
	ND_PIPE, // "|"
} t_node_kind;

typedef struct s_redirect_list	t_redirect_list;
struct s_redirect_list
{
	char			*word;
	char			*redirect;
	bool			is_ambiguous;
	t_redirect_list	*next;
};

typedef struct s_command	t_command;
struct s_command
{
	char			**word_list; // e.g. cat -option file_name
	t_redirect_list	*in_redir;
	t_redirect_list	*out_redir;
	t_redirect_list	*heredoc;
};

typedef struct s_node	t_node;
struct s_node
{
	t_node_kind	kind;
	t_command	command;
	t_token		*word_list;
	size_t		word_list_size;
	t_node		*left;
	t_node		*right;
};

// ------------- builtin -----------------
typedef enum e_builtin_kind
{
	BUILTIN_ECHO,	// echo
	BUILTIN_CD,			// cd
	BUILTIN_PWD,		// pwd
	BUILTIN_EXPORT,		// export
	BUILTIN_UNSET,		// unset
	BUILTIN_ENV,		// env
	BUILTIN_EXIT,		// exit
}	t_builtin_kind;
// ------------- builtin -----------------

// ------------- env -----------------
typedef struct s_mshell	t_mshell;
struct s_mshell
{
	t_envvar	*envlist;
	bool 		interrupt;
};

t_mshell	*g_mshell;


// ------------- env -----------------

// ------------- builtin -----------------
// echo.c
void			echo_(char **args);

// export.c
void			export_(char **cmds);

// unset.c
void			unset_(char **args);

// env.c
void			env_(char **args);

// exit.c
void			exit_(char **cmds);
// void			msh_exit(int status);

// pwd.c
void			pwd_();

// cd.c
void			cd_(char **cmds);

// builtin_utils.c
void			print_command_usage(char *name, char *usage);
void			print_command_usage2(char *name, char *usage);
void			error_option(char *builtin_name, char *option_name);
void			error_option2(char *builtin_name, char option);
void			error_ident(char *builtin_name, char *ident);
// ------------- builtin -----------------

// set_exit_status.c
void	set_exit_status(int status);

// utils.c
char			*here_doc(char *eos);
int				check_op(char *s);
size_t			get_word_len(char *p, t_token_kind kind, char *str);
size_t			get_valiable_name_len(char *str);
bool			is_redirect_kind(t_token_kind kind);
t_redirect_list	*_redir_lstlast(t_redirect_list *lst);

// parse.c
t_node			*command_line(t_token **tok);

// expansion.c
void			expansion(t_node *node);

// expansion_utils.c
char			*expand_str(char *str);
void			join_token_and_token_prev(t_token **token)
char			*strdup_before_valiable(char *tmp, char *variable_name)
static			t_token	*new_token(t_token_kind kind, char *p, size_t len)

// sum_up_token_in_quote.c
void			sum_up_token_in_quote(t_node *node);

//handle_token_in_quotes.c
void			handle_token_in_quotes(t_token *token);

// void	create_t_command.c
void			create_t_command(t_node *node);

// exec.c
void			handle_command(t_node *node);
void 			exec(char **commands);

// built_in_command.c
bool			is_exec_built_in(t_node *node, t_command redir);
bool			is_exec_built_in_in_child(char **cmds);
void			_exec_builtin_cmd(t_builtin_kind kind, char **cmds);

// exec_utils.c
char			**get_command_path(t_envvar *envlist);
char			**_alloc_word_list(t_token *tok, size_t size);
void			handle_fd(int close_fd, int dup_fd, int fd);
bool			is_exec_cmd_with_full_path(char **cmds);

// signal.c
void				display_new_prompt(int signal);
void				back_to_new_prompt(int signal);
void				interrupt(int signal);

// run_command_line.c
void			run_command_line(char *str);
//tmp
t_node			*main_(char *str);

// redirect.c
int				handle_in_redir(t_redirect_list *redirect);
int				handle_out_redir(t_redirect_list *redirect);

// here_doc.c
bool			last_is_here_doc(t_redirect_list *last);
char			*get_here_doc(char *eos);
bool			is_exec_with_here_doc(t_command command);
void			get_here_doc_form_each_node(t_node *node);

// free.c
void			free_token_list(t_token *token);
void			free_node_list(t_node *node);
void			free_double(char **p);

//debug
void			debug_node(t_node *node);
void			debug_tokenize(t_token *token);
void			debug_token(t_token *token, size_t loop_cnt);
void			_debug_command(t_command cmd);
void			_debug_strs(char **strs);

// error.c
t_node			*parse_error(t_node *node, t_token *token);
void 			error(char *str);

# endif
