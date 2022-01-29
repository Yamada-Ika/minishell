NAME	:= libblt.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
HEADER	:= -I../../include -I../../libft
SRCS	:= \
builtin_utils.c            envvar_utils_2.c           increment_shlvl.c	\
builtin_utils2.c           exit.c                     inherite_env_val.c	\
cd.c                       export.c                   my_getenv.c			\
echo.c                     generate_environ.c         pwd.c					\
env.c                      get_canonical_path.c       unset.c				\
envvar_utils_1.c           get_resize_strs_with_str.c
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
