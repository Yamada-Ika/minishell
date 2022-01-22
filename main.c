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

static void	_init_global_var(char **envp)
{
	g_mshell = ft_calloc(1, sizeof(g_mshell));
	inherite_env_val(&(g_mshell->envlist), envp);
	g_mshell->interrupt = false;
}

int main(int argc, char **argv) {
//int main(int argc, char **argv, char *envp[]) {
	char	**paths;
	extern char	**environ;
	if (argc > 1 && argv[1])
		return (0);
	_init_global_var(environ);
	using_history();
	read_history(".my_history");
//	paths = environ;
	// paths = get_command_path(g_mshell->envlist);
	paths = NULL;
	while (1)
	{
		_install_signal_handler();
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
