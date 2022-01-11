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
		// printf("minishell: command not found: %s\n", command + 1);
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(command + 1, 2);
	}
	free(command);
	free_double(paths);
}

void	pwd_()
{
	char	pathname[512];

	getcwd(pathname, 512); // getcwdはカレントディレクトリ
    printf("%s\n",pathname);
}

void	cd_(int i, char **cmds)
{
	char	pathname[512];
	DIR		*dp;
	struct dirent *dirp;

    memset(pathname, '\0', 512); // memsetはバイトメモリブロックのセット
 
    // char path[64] = "./libft";
    chdir(cmds[i]);
    printf("\n%s\n",cmds[i]);
    getcwd(pathname, 512); // getcwdはカレントディレクトリ
    printf("\n%s\n",pathname);

	// dp = opendir(pathname);
	
	// while ((dirp = readdir(dp)) != NULL)
    //     printf("%s\n", dirp->d_name);

	// closedir(dp);
}

char buf[256];
char *here;
void recursive(int i, char ***cmds, char *envp[]) {
	pid_t pid;
	int fd[2];

	// if (i == 0) {
	// 	pipe(fd);
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		close(fd[0]);
	// 		dup2(fd[1], 1);
	// 		close(fd[1]);
	// 		// int open_file = open("aa", O_RDWR);
	// 		// if (open_file == -1 || read(open_file, buf, 256) == -1)
	// 		// 	error("error");
	// 		// write(1, buf, ft_strlen(buf));
	// 		// ft_printf("%s",here);
	// 	}
	// 	else {
	// 		waitpid(pid, &sts, 0);
	// 		close(fd[1]);
	// 		dup2(fd[0], 0);
	// 		close(fd[0]);
	// 		exec(envp, cmds[i]);
	// 	}
	// 	return;
	// }
	if (i == 0)
	{
		if (ft_strncmp(cmds[i][0], "pwd", 3) == 0 && cmds[i][1] == NULL)
			pwd_();
		else
			exec(envp, cmds[i]);
		return;
	}
	

	pipe(fd);
	pid = fork();

	if (pid == 0) {
		close(fd[1]);
		dup2(fd[0], 0);
		if (ft_strncmp(cmds[i][0], "pwd", 3) == 0 && cmds[i][1] == NULL)
			pwd_();
		else
			exec(envp, cmds[i]);
		close(fd[0]);
	} 
	else {
		close(fd[0]);
		dup2(fd[1], 1);
		recursive(i - 1, cmds, envp);
		close(fd[1]);
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
	if (ft_strncmp(commands[0], "cd", 2) == 0)
	{
		cd_(1, commands);
		return;
	}
	while (cmds[i])
	{
		i++;
	}
	pid_t pid = fork();
	if (pid == 0)
	{
		// here =  here_doc("EOS");
		recursive(i - 1, cmds, envp);
		// free_double(commands);
		free_triple(cmds);
	}
	free_double(commands);
	free_triple(cmds);
	waitpid(pid, &sts, 0);
}

volatile sig_atomic_t	g_signal;

static void	ft_get_signal(int	signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}



int main(int argc, char **argv, char *envp[]) {
	char *prompt = "minishell> ";
	int i = 0;

	signal(SIGINT, ft_get_signal);
	using_history();
	read_history(".my_history"); // [ToDo]historyファイルが無いときの動作の検証
	while (1) {
		char *str = readline(prompt);
		add_history(str);
		if (ft_strncmp(str, "exit", 4) == 0)
			exit(0);
		if (*str != '\0') // 改行が入力されたか
			handle_command(envp, str);
		free(str);
	}
	// system("leaks minishell");
	write_history(".my_history");
}
