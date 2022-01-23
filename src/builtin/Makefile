NAME	:= libblt.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
HEADER	:= -I../../include -I../../libft
SRCS	:= \
builtin_utils.c    env.c              exit.c             my_getenv.c	\
cd.c               envvar_utils_1.c   export.c           pwd.c			\
echo.c             envvar_utils_2.c   inherite_env_val.c unset.c
OBJS	:= $(SRCS:%.c=%.o)
LIBFT = ../../libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	ar rc $(NAME) $(OBJS) $(LIBFT)

%.o:%.c
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
