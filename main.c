#include "minishell.h"

int sts;

void free_double(char **p)
{
	size_t i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

void free_triple(char ***p)
{
	size_t i;

	i = 0;
	while (p[i])
	{
		free_double(p[i]);
		i++;
	}
	free(p);
}

void exec(char *envp[], char **commands) {

	char *str;
	char *absolute_path;
	char *command; 
	size_t i;

	i = 0;

	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
		{
			str = ft_strdup(*envp);
			break;
		}
		envp++;
	}
	char **paths = ft_split(str + 5, ':');
	free(str);

	command = ft_strjoin("/", commands[0]);
	while (paths[i]) {
		absolute_path = ft_strjoin(paths[i], command);
		int ok = access(absolute_path, X_OK);
		if (ok == F_OK)
		{
			// call(absolute_path, commands);
			execve(absolute_path, commands, NULL);
			free(absolute_path);
			break;
		}
		free(absolute_path);
		i++;
	}
	if (paths[i] == NULL) {
		printf("minishell: command not found: %s\n", command + 1);
	}
	free(command);
	free_double(paths);
}

void recursive(int i, char ***cmds, char *envp[]) {
	pid_t pid;
	int fd[2];

	if (i == 0) {
		// execvp(cmds[i][0], cmds[i]);
		exec(envp, cmds[i]);
		return;
	}

	pipe(fd);
	pid = fork();
	
	if (pid == 0) {
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		recursive(i - 1, cmds, envp);
	} 
	else {
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		// execvp(cmds[i][0], cmds[i]);
		exec(envp, cmds[i]);
	}
}

void call(char *pathname, char **argv) {
	// printf("pathname:%s\n", pathname);
	pid_t pid = fork();
	if (pid == 0)
		execve(pathname, argv, NULL);
	waitpid(pid, &sts, 0);
}

void    handle_command(char *envp[], char *command)
{
	char **commands = ft_split(command, ' ');
	size_t  i = 0;
	char ***cmds = ft_split_triple((const char**)commands, "|");
	while (cmds[i])
	{
		i++;
	}
	pid_t pid = fork();
	if (pid == 0)
	{
		if (i == 1)
			exec(envp, commands);
		else
			recursive(i - 1, cmds, envp);
		// free_double(commands);
		free_triple(cmds);
	}
	free_double(commands);
	free_triple(cmds);
	waitpid(pid, &sts, 0);
}


int main(int argc, char **argv, char *envp[]) {
	char *prompt = "minishell> ";
	int i = 0;
	
	using_history();
	read_history(".my_history"); // [ToDo]historyファイルが無いときの動作の検証
	while (1) {
		char *str = readline(prompt);
		add_history(str);
		handle_command(envp, str);
		free(str);
	}
	// system("leaks minishell");
	write_history(".my_history");
}
