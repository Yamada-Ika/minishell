#include "minishell.h"

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

int main(int argc, char **argv, char *envp[]) {
	char	**paths;
	char	**splitted_newline;
	size_t	i;

	if (argc > 1 && argv[1])
		return (0);
	_init_global_var(envp);
	_install_signal_handler();
	using_history();
	read_history(".my_history");
	paths = get_command_path(g_mshell->envlist);
	i = 0;
	while (1)
	{
		char *str = readline("minishell> ");
		add_history(str);
		splitted_newline = ft_split(str, '\n');
		if (splitted_newline == NULL)
			exit(0);
		while (splitted_newline[i] != NULL)
		{
			if (splitted_newline[i][0] != '\0')
				run_command_line(str, paths);
			i++;
		}
		if (str == NULL)
			exit(0);
		free_double(splitted_newline);
		free(str);
	}
	write_history(".my_history");
}
