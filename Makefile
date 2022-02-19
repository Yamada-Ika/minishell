NAME		:= minishell
LIBFT		:= libft/libft.a
BUILTIN		:= src/builtin/libblt.a
EXEC		:= src/exec/libex.a
EXPANDER	:= src/expander/libexpander.a
LEXAR		:= src/lexer/liblex.a
PARSER		:= src/parser/libprs.a
UTILS		:= src/utils/libutl.a

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
LDFLAGS 	:= -lreadline -lhistory -L$(shell brew --prefix readline)/lib
INCLUDE 	:= -Iinclude/ -I$(shell brew --prefix readline)/include -Ilibft -Ibuiltin

SRCS		:= src/main.c src/run_command_line.c
OBJS 		:= $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(BUILTIN) $(EXEC) $(EXPANDER) $(LEXAR) $(PARSER) $(UTILS)
	echo > ~/.inputrc set echo-control-characters off
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LEXAR) $(PARSER) $(EXPANDER) $(EXEC) $(BUILTIN) $(UTILS) $(LIBFT) $(LDFLAGS)
$(LIBFT): empty
	make -C libft

$(BUILTIN): empty
	make -C src/builtin
$(EXEC): empty
	make -C src/exec
$(EXPANDER): empty
	make -C src/expander
$(LEXAR): empty
	make -C src/lexer
$(PARSER): empty
	make -C src/parser
$(UTILS): empty
	make -C src/utils

empty:

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	make clean -C libft
	make clean -C src/builtin
	make clean -C src/exec
	make clean -C src/expander
	make clean -C src/lexer
	make clean -C src/parser
	make clean -C src/utils

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(BUILTIN)
	$(RM) $(EXEC)
	$(RM) $(EXPANDER)
	$(RM) $(LEXAR)
	$(RM) $(PARSER)
	$(RM) $(UTILS)

re: fclean all

.PHONY: all clean fclean re empty test norm
