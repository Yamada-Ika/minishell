NAME	:= libblt.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
HEADER	:= -I../../include -I../../libft
SRCS	:= \
builtin_utils.c            cdpath.c                   generate_environ.c\
builtin_utils2.c           echo.c                     get_canonical_path.c\
cd.c                       env.c                      get_resize_strs_with_str.c\
cd_utils.c                 envvar_utils_1.c           increment_shlvl.c\
cd_utils2.c                envvar_utils_2.c           inherite_env_val.c\
cd_utils3.c                exit.c                     my_getenv.c\
cd_utils4.c                export.c                   pwd.c\
cd_utils5.c                export_utils.c             unset.c
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
