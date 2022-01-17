NAME = minishell
LIBFT = libft/libft.a
DEBUG = test/debug.a
CC = gcc
CFLAGS = -g -fsanitize=address #-Wall -Wextra -Werror
LDFLAGS = -lreadline -lhistory -L$(shell brew --prefix readline)/lib
INCLUDE = -Iinclude/ -I$(shell brew --prefix readline)/include -Iinclude
# SRCS =  samples/pipe.c
 SRCS =  main.c  run_command_line.c tokenize.c utils.c parse.c \
   		expansion.c handle_token_in_quotes.c create_t_command.c exec.c signal.c
#SRCS = test.c tokenize.c utils.c parse.c  expansion.c handle_token_in_quotes.c create_t_command.c exec.c test/debug.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(DEBUG)
	#$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(DEBUG)  $(LIBFT) $(LDFLAGS)
$(LIBFT): empty
	make -C libft
$(DEBUG): empty
	make -C test
empty:

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	make clean -C libft
	make clean -C test
fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(DEBUG)
re: fclean all
# test: $(NAME)
# 	$(CC) $(CFLAGS) $(NAME) main.c &&./a.out
# t: $(NAME)
# 	$(CC) $(CFLAGS) $(NAME) main.c
# test-: $(NAME)
# 	$(CC) $(NAME) main.c &&./a.out

.PHONY: all clean fclean re empty
