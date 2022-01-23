NAME	:= libprs.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
HEADER	:= -I../../include -I../../libft
SRCS	:= parse.c
OBJS	:= $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
