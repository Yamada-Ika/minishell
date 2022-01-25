#include "minishell.h"

//__attribute__((destructor))
//void	destructor(void)
//{
//	int	status;
//
//	system("leaks minishell");
////	status = system("leaks debug &> leaksout");
////	if (status)
////	{
////		write(2, "leak!!!\n", 8);
////		system("cat leaksout >/dev/stderr");
////		exit(1);
////	}
//}

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

//	g_mshell = ft_calloc(1, sizeof(g_mshell));
	inherite_env_val(&(g_mshell.envlist), environ);
	set_exit_status(0);
	g_mshell.interrupt = false;
	_set_pwd();
}

int	main(int argc, char **argv)
{
	char	*cmd_line;

	if (argc > 1 && argv[1])
		return (0);
	_init_global_var();
	using_history();
	read_history(".my_history");
	while (true)
	{
		_install_signal_handler();
		cmd_line = readline("minishell> ");
		if (cmd_line == NULL)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			exit(0);
		}
		if (*cmd_line != '\0')
		{
			add_history(cmd_line);
			run_command_line(cmd_line);
		}
		free(cmd_line);
	}
	write_history(".my_history");
}
