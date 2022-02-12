#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*cmd_line;

	if (argc > 1 && argv[1])
		return (0);
	init_global_var();
	while (true)
	{
		install_signal_handler();
		cmd_line = readline("minishell> ");
		if (is_eof_sent(cmd_line))
			exit_minishell();
		if (!is_only_newline(cmd_line))
		{
			add_history(cmd_line);
			run_command_line(cmd_line);
		}
		free(cmd_line);
	}
}
