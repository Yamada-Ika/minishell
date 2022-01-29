#ifndef ENVVAR_H
# define ENVVAR_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# include "../libft/libft.h"

typedef struct s_envvar	t_envvar;
struct s_envvar
{
	char		*key;
	char		*val;
	t_envvar	*next;
};

// env.c
void		msh_env(t_envvar *envs);

// export.c
void		msh_export(t_envvar **envs, char *key, char *val);

// exit.c
void		exit_(char **cmds);

// unset.c
void		msh_unset(t_envvar **envs, char *key);

// my_getenv.c
char		*my_getenv(t_envvar *envs, char *key);

// inherite_env_val.c
void		inherite_env_val(t_envvar **env_list, char **envp);

// envvar_utils.c
t_envvar	*new_envlist(char *key, char *val);
void		add_envlist(t_envvar *olds, t_envvar *new);
t_envvar	*get_envlistlast(t_envvar *envs);
void		delete_envvar_contents(char *key, char *val);
void		delete_envvar(t_envvar *env);
void		delete_envlists(t_envvar *env);
t_envvar	*get_envvar_with_key(t_envvar *envlist, char *key);
void		replace_val(t_envvar *env, char *val);
bool		is_exist_key(t_envvar *envlist, char *key);
void	increment_shlvl(void);

#endif
