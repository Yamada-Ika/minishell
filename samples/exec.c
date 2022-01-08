#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    pid_t pid = fork();
    if (pid == 0)
        execve("/bin/ls", argv, NULL);
    int sts;
    waitpid(pid, &sts, 0);
    int i = 0;
    for(;;) i = 0;
}
