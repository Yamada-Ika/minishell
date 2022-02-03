NAME	:= libutl.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
HEADER	:= -I../../include -I../../libft -I$(shell brew --prefix readline)/include
LDFLAGS 	:= #-lreadline -lhistory -L$(shell brew --prefix readline)/lib
SRCS	:= \
error.c                  main_utils.c\
free1.c                  redirect.c\
free2.c                  set_exit_status.c\
here_doc.c               signal.c\
init_global_variable.c   utils.c\
install_signal_handler.c utils2.c
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
