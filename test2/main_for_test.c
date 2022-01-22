#include "minishell.h"

static void	_install_signal_handler(void)
{
	signal(SIGINT, (void *)display_new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	_init_global_var()
{
	extern char	**environ;

	g_mshell = ft_calloc(1, sizeof(g_mshell));
	inherite_env_val(&(g_mshell->envlist), environ);
	g_mshell->interrupt = false;
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
		if (splitted_newline == NULL)
			exit(0);
		i = 0;
		while (splitted_newline[i] != NULL)
		{
			if (splitted_newline[i][0] != '\0')
				run_command_line(cmd_line);
			i++;
		}
		free_double(splitted_newline);
		free(cmd_line);
	}
	write_history(".my_history");
}
