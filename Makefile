NAME		:= minishell
LIBFT		:= libft/libft.a
BUILTIN		:= src/builtin/libblt.a
EXEC		:= src/exec/libex.a
EXPANDER	:= src/expander/libexpander.a
LEXAR		:= src/lexar/liblex.a
PARSER		:= src/parser/libprs.a
UTILS		:= src/utils/libutl.a

DEBUG		:= test/debug.a
CC			:= gcc
CFLAGS		:= -g -Wall -Wextra -Werror #-fsanitize=address
LDFLAGS 	:= -lreadline -lhistory -L$(shell brew --prefix readline)/lib
INCLUDE 	:= -Iinclude/ -I$(shell brew --prefix readline)/include -Ilibft -Ibuiltin



# If `make` use main.c, `make test` use test2/main_for_test.c
ifdef ADD_MAIN_FOR_TEST
SRCS	+= test2/main_for_test.c
else
SRCS	+= src/main.c src/run_command_line.c
endif

BUITIN_SRCS	:= $(addprefix builtin/, $(BUITIN_SRCS))
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(DEBUG) $(BUILTIN) $(EXEC) $(EXPANDER) $(LEXAR) $(PARSER) $(UTILS)
	echo > ~/.inputrc set echo-control-characters off
	#$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(DEBUG)  $(LIBFT) $(BUILTIN) $(EXEC) $(EXPANDER) $(LEXAR) $(PARSER) $(UTILS) $(LDFLAGS)

$(LIBFT): empty
	make -C libft

$(DEBUG): empty
	make -C test
$(BUILTIN): empty
	make -C src/builtin
$(EXEC): empty
	make -C src/exec
$(EXPANDER): empty
	make -C src/expander
$(LEXAR): empty
	make -C src/lexar
$(PARSER): empty
	make -C src/parser
$(UTILS): empty
	make -C src/utils

empty:

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

test:
	touch test2/main_for_test.c
	make ADD_MAIN_FOR_TEST=1
	cd test2/ && ./run_minishell_test.sh

clean:
	$(RM) $(OBJS)
	make clean -C libft
	make clean -C src/builtin
	make clean -C src/exec
	make clean -C src/expander
	make clean -C src/lexar
	make clean -C src/parser
	make clean -C src/utils
	make clean -C test

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(DEBUG)
	$(RM) $(BUILTIN)
	$(RM) $(EXEC)
	$(RM) $(EXPANDER)
	$(RM) $(LEXAR)
	$(RM) $(PARSER)
	$(RM) $(UTILS)

re: fclean all

# test: $(NAME)
# 	$(CC) $(CFLAGS) $(NAME) main.c &&./a.out
# t: $(NAME)
# 	$(CC) $(CFLAGS) $(NAME) main.c
# test-: $(NAME)
# 	$(CC) $(NAME) main.c &&./a.out

.PHONY: all clean fclean re empty test
