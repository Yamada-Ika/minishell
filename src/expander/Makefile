NAME = libexpander.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I ../../include/
SRCS = expansion.c handle_token_in_quotes.c expansion_utils.c

OBJS = $(SRCS:%.c=%.o)

LIBFT = ../../libft/libft.a
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	ar rc $(NAME) $(OBJS) $(LIBFT)
%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
