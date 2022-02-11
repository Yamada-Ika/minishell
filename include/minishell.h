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
# include <stdbool.h>
# include <dirent.h>
# include <sys/stat.h>

// env
# include "envvar.h"

# define ERROR -1
# define ERRNO_INIT_VAL 0

/**
 * t_token_kind is a kind of token which generated at lexer called.
 * 
 * EMPTY           : invalid kind
 * TK_OP_DOUBLE_GR : output-redirection with append mode (">>")
 * TK_OP_SINGLE_LS : heredocument ("<<")
 * TK_OP_LS        : input-redirection ("<")
 * TK_OP_GR        : output-redirection (">")
 * TK_OP_PIPE      : pipe ("|")
 * TK_OP_DOLLAR    : environment variable ("$")
 * TK_WORD         : command etc...
 * TK_EOF          : end of token
 */
typedef enum e_token_kind		t_token_kind;
enum e_token_kind
{
	EMPTY = -1,
	TK_OP_DOUBLE_GR,
	TK_OP_SINGLE_LS,
	TK_OP_LS,
	TK_OP_GR,
	TK_OP_PIPE,
	TK_OP_DOLLAR,
	TK_WORD,
	TK_WORD_IN_SINGLE_Q,
	TK_WORD_IN_DOUBLE_Q,
	TK_EOF,
};

typedef struct s_token			t_token;
struct s_token
{
	t_token_kind	kind;
	t_token			*next;
	t_token			*prev;
	char			*str;
	size_t			len;
	bool			is_join_prev;
};

/**
 * t_node_kind is a kind of node which generated at parser called.
 * 
 * ND_CMD  : command (e.g. cat)
 * ND_PIPE : pipe ("|")
 */
typedef enum e_node_kind
{
	ND_CMD,
	ND_PIPE,
}	t_node_kind;

typedef struct s_redirect_list	t_redirect_list;
struct s_redirect_list
{
	char			*word;
	char			*redirect;
	bool			is_ambiguous;
	t_redirect_list	*next;
};

// char			**word_list; // e.g. cat -option file_name
typedef struct s_command		t_command;
struct s_command
{
	char			**word_list;
	t_redirect_list	*in_redir;
	t_redirect_list	*out_redir;
	t_redirect_list	*heredoc;
};

typedef struct s_node			t_node;
struct s_node
{
	t_node_kind	kind;
	t_command	command;
	t_token		*word_list;
	size_t		word_list_size;
	t_node		*left;
	t_node		*right;
};

// BUILTIN_ECHO,	// echo
// BUILTIN_CD,			// cd
// BUILTIN_PWD,		// pwd
// BUILTIN_EXPORT,		// export
// BUILTIN_UNSET,		// unset
// BUILTIN_ENV,		// env
// BUILTIN_EXIT,		// exit
typedef enum e_builtin_kind
{
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT,
}	t_builtin_kind;

typedef struct s_mshell			t_mshell;
struct s_mshell
{
	t_envvar	*envlist;
	char		*pwd;
	char		*pwd2;
	char		*old_pwd;
	bool		interrupt;
};

t_mshell						g_mshell;

// echo.c
void			echo_(char **args);

// export.c
void			export_(char **cmds);

// export_utils.c
bool			is_invalid_key(char *key);
void			set_key_and_val(char **key, char **val, char *k, char *v);

// unset.c
void			unset_(char **args);

// env.c
void			env_(char **args);

// exit.c
void			exit_(char **cmds);
// void			msh_exit(int status);

// pwd.c
void			pwd_(void);

// cd.c
void			cd_(char **cmds);

// cd_utils
bool			is_non_arguments(char **args);
bool			is_abs_path(char *path);
bool			is_arg_path_start_from_current_dir(char *path);
bool			cannot_get_home_path(char **cmds, char **arg_path);
bool			can_chdir_with_cdpath(char *arg_path, char **cano_path);

void			update_pwd(char *cur_dir_path);
void			cd_do_success_routine(char *cano_path);
void			cd_do_cdpath_routine(char *cano_path);
void			cd_do_error_routine(char *cano_path, char *arg_path);

char			*gen_abs_path(char *dst);
char			*get_home_path(void);
char			*gen_abs_to_cano_path(char *abs_path);
char			*gen_rel_to_cano_path(char *rel_path);

char			*gen_cano_path_from_cdpath(char *arg_path);

int				chdir_for_cd(char *cano_path, char *arg_path);

// builtin_utils.c
void			print_command_usage2(char *name, char *usage);
void			error_option(char *builtin_name, char *option_name);
void			error_option2(char *builtin_name, char option);
void			error_with_errno(char *builtin_name, char *arg);
void			error_ident(char *builtin_name, char *ident);

// builtin_utils2.c
void			print_command_usage(char *name, char *usage);

// get_canonical_path.c
char			*get_canonical_path(char *abs_path);

// get_resize_strs_with_str.c
char			**get_resize_strs_with_str(char **strs, char *s);

// generate_environ.c
char			**generate_environ(void);

// for main.c
// init_global_variable.c
void			init_global_var(void);

// install_signal_handler.c
void			install_signal_handler(void);

bool			is_eof_sent(char *read_str);
void			exit_minishell(void);
bool			is_only_newline(char *read_str);

// set_exit_status.c
void			set_exit_status(int status);
void			add_exit_status_to_env(int status);
int				get_exit_status(int status);

// lexer.c
t_token			*lexer(char *p);
void			debug_tokenize(t_token *token);

// tokenize_utils.c
void			skip_space(char **s);
bool			is_quote_closed(char c, t_token_kind kind);
int				check_op(char *s);

// utils.c
//char			*here_doc(char *eos);
size_t			get_word_len(char *p, t_token_kind kind, char *str);
size_t			get_env_name_len(char *str);
bool			is_redirect_kind(t_token_kind kind);
bool			can_c_be_env_name(char c);
bool			is_env_name(char *str);

// utils2.c
void			ft_dup2(int oldfd, int newfd);
int				ft_dup(int fd);
void			ft_pipe(int *fd);
pid_t			ft_fork(void);

// parse.c
t_node			*parser(t_token **tok);

// expander.c
void			expander(t_node *node);

// expansion_utils.c
char			*expand_str(char *str);
void			join_token_and_token_prev(t_token **token);
char			*strdup_before_valiable(char *tmp, char *variable_name);
size_t			join_valiable(char **p, t_token **tok);

// expansion_utils2.c
t_token			*new_token_tk_word(t_token_kind kind, char *p, size_t len);

// sum_up_token_in_quote.c
void			sum_up_token_in_quote(t_node *node);

//handle_token_in_quotes.c
void			handle_token_in_quotes(t_token *token);

// void	create_t_command.c
void			create_t_command(t_node *node);

// exec.c
void			exec_command_line(t_node *node);
void			exec(char **commands);

// built_in_command.c
bool			is_exec_built_in(t_node *node, t_command redir);
bool			is_exec_built_in_in_child(char **cmds);
void			_exec_builtin_cmd(t_builtin_kind kind, char **cmds);

// exec_utils.c
char			**get_command_path(t_envvar *envlist);
char			**_alloc_word_list(t_token *tok, size_t size);
void			handle_fd(int close_fd, int dup_fd, int fd);
void			exec_cmd_with_path(char **cmds, char **environ);
char			*exec_cmd(char *path, char **cmds, char **environ);

// signal.c
void			display_new_prompt(int signal);
void			back_to_new_prompt(int signal);
void			interrupt(int signal);

// run_command_line.c
void			run_command_line(char *str);
//tmp
t_node			*main_(char *str);

// redirect.c
int				handle_in_redir(t_redirect_list *redirect);
int				handle_out_redir(t_redirect_list *redirect);
t_redirect_list	*_redir_lstlast(t_redirect_list *lst);

// here_doc.c
bool			last_is_here_doc(t_redirect_list *last);
char			*get_here_doc(char *eos);
bool			is_exec_with_here_doc(t_command command);
void			get_here_doc_form_each_node(t_node *node);

// free1.c
void			free_token_list(t_token *token);
void			free_node_list(t_node *node);

// free2.c
void			free_strs(char **strs);

//debug
void			debug_node(t_node *node);
void			debug_tokenize(t_token *token);
void			debug_token(t_token *token, size_t loop_cnt);
void			_debug_command(t_command cmd);
void			_debug_strs(char **strs);

// error.c
t_node			*parse_error(t_node *node, t_token *token);
void			error(char *str);
t_token			*tokenize_error(t_token *head, t_token *cur);
void			error_message(char *m, char *m2);
void			error_exit_with_message(int stats, char *m, char *m2);

#endif
