NAME = libex.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I ../../include/
SRCS = built_in_command.c create_t_command.c exec.c
OBJS = $(SRCS:%.c=%.o)

LIBFT = ../../libft/libft.a
all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
