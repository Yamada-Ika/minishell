#include "minishell.h"

int main(int argc, char **argv, char *envp[]) {
	char *prompt = "minishell> ";
	char	**paths;
	int i = 0;

	signal(SIGINT, ft_get_signal);
	signal(SIGQUIT	, SIG_IGN);
	using_history();
	read_history(".my_history"); // [ToDo]historyファイルが無いときの動作の検証
	paths = get_command_path(envp);
	while (1) {
		char *str = readline(prompt);
		add_history(str);
		if (str == NULL)
			exit(0);
		if (ft_strncmp(str, "exit", 4) == 0)
			exit(0);
		if (*str != '\0') // 改行が入力されたか
			run_command_line(str, paths);
		free(str);
	}
	// system("leaks minishell");
	write_history(".my_history");
}
