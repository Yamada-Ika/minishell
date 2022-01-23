NAME	:= libutl.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
HEADER	:= -I../../include -I../../libft -I$(shell brew --prefix readline)/include
LDFLAGS 	:= #-lreadline -lhistory -L$(shell brew --prefix readline)/lib
SRCS	:= free.c here_doc.c redirect.c set_exit_status.c signal.c utils.c error.c
OBJS	:= $(SRCS:%.c=%.o)
LIBFT = ../../libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	ar rc $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

%.o:%.c
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
