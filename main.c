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
	signal(SIGINT, display_new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	_init_global_var(char **envp)
{
	g_mshell = ft_calloc(1, sizeof(g_mshell));
	inherite_env_val(&(g_mshell->envlist), envp);
	g_mshell->interrupt = false;
}

int main(int argc, char **argv, char *envp[]) {
	char	**paths;
	pid_t	pid;
	int		sts;

	_init_global_var(envp);
	_install_signal_handler();
	using_history();
	if (read_history(".my_history") != 0)
		exit(1);
	while (true)
	{
		paths = get_command_path(envp);
		// paths = get_command_path(g_mshell->envlist);
		char *str = readline("minishell> ");
		add_history(str);
		if (str == NULL)
			exit(0);
		if (*str != '\0')
			run_command_line(str, paths);
		free(str);
	}
	write_history(".my_history");
}
