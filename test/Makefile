NAME = debug.a
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
INCLUDE = -I ../include
SRCS = debug.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) $(HEADER) -o $@ -c $<
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
