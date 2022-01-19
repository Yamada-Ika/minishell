#ifndef ENVVAR_H
#define ENVVAR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_envvar t_envvar;
struct s_envvar
{
	char		*key;
	char		*val;
	t_envvar	*next;
};

// env.c
void	msh_env(t_envvar *envs);

// export.c
void	msh_export(t_envvar **envs, char *key, char *val);

// unset.c
void	msh_unset(t_envvar **envs, char *key);

// envvar_utils.c
t_envvar	*new_envlist(char *key, char *val);
void		add_envlist(t_envvar *olds, t_envvar *new);
t_envvar	*get_envlistlast(t_envvar *envs);
void		delete_envvar_contents(char *key, char *val);
void		delete_envlists(t_envvar *env);

#endif