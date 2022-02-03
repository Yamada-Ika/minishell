#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*cmd_line;

	if (argc > 1 && argv[1])
		return (0);
	init_global_var();
	using_history();
	read_history(".minishell_history");
	while (true)
	{
		install_signal_handler();
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
			write_history(".my_history");
		}
		free(cmd_line);
	}
}
