NAME	:= libutl.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
HEADER	:= -I../../include -I../../libft
SRCS	:= free.c here_doc.c redirect.c set_exit_status.c signal.c utils.c
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
