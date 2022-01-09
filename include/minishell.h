#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"
#include <stdbool.h>

char	***ft_split_triple(char const **strs, char *sets);

typedef enum e_token_kind
{
	TK_RESERVED, // 予約語
	// TK_META,     // メタ文字 (\, ...)
	TK_PIPE,     // パイプ
	// TK_COMMAND,  // コマンドトークン
	TK_STRING,   // 文字列(コマンド、コマンドの引数、etc)
	TK_EOF,      // 入力の終わりを表すトークン
}	t_token_kind;

typedef struct s_token
{
	t_token_kind	kind;
	struct s_token	*next;
	char			*str;
}	t_token;

# endif