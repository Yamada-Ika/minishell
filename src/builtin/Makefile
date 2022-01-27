NAME	:= libblt.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
HEADER	:= -I../../include -I../../libft
SRCS	:= \
builtin_utils.c            env.c                      export.c                   inherite_env_val.c	\
builtin_utils2.c           envvar_utils_1.c           generate_environ.c         my_getenv.c		\
cd.c                       envvar_utils_2.c           get_canonical_path.c       pwd.c				\
echo.c                     exit.c                     get_resize_strs_with_str.c unset.c
OBJS	:= $(SRCS:%.c=%.o)
OBJS	:= $(addprefix obj/, $(OBJS))
LIBFT = ../../libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	ar rc $(NAME) $(OBJS) $(LIBFT)

obj/%.o:%.c
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
