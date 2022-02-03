NAME	:= libutl.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
HEADER	:= -I../../include -I../../libft -I$(shell brew --prefix readline)/include
LDFLAGS 	:= #-lreadline -lhistory -L$(shell brew --prefix readline)/lib
SRCS	:= \
error.c                  init_global_variable.c   signal.c\
free1.c                  install_signal_handler.c utils.c\
free2.c                  redirect.c               utils2.c\
here_doc.c               set_exit_status.c
OBJS	:= $(SRCS:%.c=%.o)
OBJS	:= $(addprefix obj/, $(OBJS))
LIBFT = ../../libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	ar rc $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

obj/%.o:%.c
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
