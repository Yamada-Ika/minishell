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
		if (is_eof_sent(cmd_line))
			exit_minishell();
		if (*cmd_line != '\0')
		{
			add_history(cmd_line);
			run_command_line(cmd_line);
			write_history(".my_history");
		}
		free(cmd_line);
	}
}
