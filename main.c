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

int main(int argc, char **argv, char *envp[]) {
	char	**paths;
	pid_t	pid;
	int		sts;

	env_init(envp);
	g_mshell->interrupt = false;
	signal(SIGINT, (void *)ft_get_signal);
	signal(SIGQUIT, SIG_IGN);
	using_history();
	read_history(".my_history"); // [ToDo]historyファイルが無いときの動作の検証
	paths = get_command_path(envp);
	while (1)
	{
		char *str = readline("minishell> ");
		add_history(str);
		if (str == NULL)
			exit(0);
		if (*str != '\0') // 改行が入力されたか
			run_command_line(str, paths);
		free(str);
	}
	write_history(".my_history");
}
