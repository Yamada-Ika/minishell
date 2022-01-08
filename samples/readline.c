#include "stdio.h"    
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *prompt = "minishell>";
    
    using_history();
    read_history(".my_history"); // [ToDo]historyファイルが無いときの動作の検証
    while (1) {
        char *str = readline(prompt);
        add_history(str);
        printf("%s\n", str);
    }
    write_history(".my_history");
}

// build:
//   gcc read.c -L/usr/include -lreadline
