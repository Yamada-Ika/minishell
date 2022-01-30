#ifndef DEBUG_H
# define DEBUG_H

# include "../include/minishell.h"

void		debug_node(t_node *node);
void		debug_tokenize(t_token *token);
static void	debug_token(t_token *token, size_t loop_cnt);
static void	_debug_command(t_command cmd);

#endif
