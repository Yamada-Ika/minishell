#include <unistd.h>

int main() {
    char buf[4096];

    write(1, "minishell> ", 11);
    int byte = read(0, buf, 4096);
    write(1, buf, byte);
}
