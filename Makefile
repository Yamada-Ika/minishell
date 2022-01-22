NAME	:= minishell
LIBFT	:= libft/libft.a
DEBUG	:= test/debug.a
CC		:= gcc
CFLAGS	:= -g -Wall -Wextra -Werror #-fsanitize=address
LDFLAGS := -lreadline -lhistory -L$(shell brew --prefix readline)/lib
INCLUDE := -Iinclude/ -I$(shell brew --prefix readline)/include -Ilibft -Ibuiltin

SRCS	:= \
built_in_command.c       free.c                   redirect.c               utils.c	\
create_t_command.c       handle_token_in_quotes.c run_command_line.c				\
exec.c                   here_doc.c               signal.c							\
expansion.c              parse.c                  tokenize.c
SRCS	:= $(addprefix src/, $(SRCS))

# If `make` use main.c, `make test` use test2/main_for_test.c
ifdef ADD_MAIN_FOR_TEST
SRCS	+= test2/main_for_test.c
else
SRCS	+= main.c
endif

BUITIN_SRCS	:= 	echo.c cd.c pwd.c export.c env.c unset.c exit.c \
				envvar_utils_1.c envvar_utils_2.c my_getenv.c inherite_env_val.c \
				builtin_utils.c
BUITIN_SRCS	:= $(addprefix builtin/, $(BUITIN_SRCS))
SRCS		+= $(BUITIN_SRCS)
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(DEBUG)
	#$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(DEBUG)  $(LIBFT) $(LDFLAGS)

$(LIBFT): empty
	make -C libft

$(DEBUG): empty
	make -C test

empty:

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

test:
	touch test2/main_for_test.c
	make ADD_MAIN_FOR_TEST=1
	cd test2/ && ./run_minishell_test.sh

clean:
	$(RM) $(OBJS)
	make clean -C libft
	make clean -C test

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(DEBUG)

re: fclean all

# test: $(NAME)
# 	$(CC) $(CFLAGS) $(NAME) main.c &&./a.out
# t: $(NAME)
# 	$(CC) $(CFLAGS) $(NAME) main.c
# test-: $(NAME)
# 	$(CC) $(NAME) main.c &&./a.out

.PHONY: all clean fclean re empty test
