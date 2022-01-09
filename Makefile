NAME = minishell
LIBFT = libft/libft.a
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
# SRCS =  samples/pipe.c
SRCS =  main.c ft_split_triple.c
OBJS = $(SRCS:%.c=%.o)
INCLUDE = -I include/

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT) -L/usr/include -lreadline

$(LIBFT): empty
	make -C libft
empty:

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	make clean -C libft
fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
re: fclean all
# test: $(NAME)
# 	$(CC) $(CFLAGS) $(NAME) main.c &&./a.out
# t: $(NAME)
# 	$(CC) $(CFLAGS) $(NAME) main.c
# test-: $(NAME)
# 	$(CC) $(NAME) main.c &&./a.out

.PHONY: all clean fclean re empty