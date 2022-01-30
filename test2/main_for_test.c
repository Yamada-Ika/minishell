#include "minishell.h"

static void	_install_signal_handler(void)
{
	signal(SIGINT, (void *)display_new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	_set_pwd(void)
{
	char	*pwd_path;

	pwd_path = getcwd(NULL, 0);
	if (pwd_path == NULL)
	{
		ft_putstr_fd("shell-init: error retrieving current directory: \
getcwd: cannot access parent directories: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(0);
	}
	g_mshell.pwd = pwd_path;
}

static	void	_init_global_var(void)
{
	extern char	**environ;

	inherite_env_val(&(g_mshell.envlist), environ);
	msh_unset(&(g_mshell.envlist), "OLDPWD");
	msh_export(&(g_mshell.envlist), "OLDPWD", NULL);
	increment_shlvl();
	set_exit_status(0);
	g_mshell.interrupt = false;
	_set_pwd();
}

static void	_frees(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int main(int argc, char **argv)
{
	char	**splitted_newline;
	char	*cmd_line;
	size_t	i;

	if (argc > 1 && argv[1])
		return (0);
	_init_global_var();
	_install_signal_handler();
	using_history();
	read_history(".my_history");
	while (true)
	{
		cmd_line = readline("minishell> ");
		if (cmd_line == NULL)
			exit(0);
		add_history(cmd_line);
		splitted_newline = ft_split(cmd_line, '\n');
		// splitted_newline = ft_split(cmd_line, ';');
		// _debug_strs(splitted_newline);
		if (splitted_newline == NULL)
			exit(0);
		i = 0;
		while (splitted_newline[i] != NULL)
		{
			if (splitted_newline[i][0] != '\0')
				run_command_line(splitted_newline[i]);
			i++;
		}
		_frees(splitted_newline);
		free(cmd_line);
	}
	write_history(".my_history");
}
