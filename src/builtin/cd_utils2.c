#include "minishell.h"

static void	_update_pwd(char *key, char *path)
{
	if (!is_exist_key(g_mshell.envlist, key))
		return ;
	if (path != NULL)
		msh_export(&(g_mshell.envlist), key, path);
	else
		msh_export(&(g_mshell.envlist), key, "");
}

void	update_pwd(char *cur_dir_path)
{
	_update_pwd("OLDPWD", my_getenv(g_mshell.envlist, "PWD"));
	_update_pwd("PWD", cur_dir_path);
	free(g_mshell.old_pwd);
	g_mshell.old_pwd = g_mshell.pwd;
	g_mshell.pwd = cur_dir_path;
	g_mshell.pwd2 = cur_dir_path;
}
