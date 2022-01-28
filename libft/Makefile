NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADER = -I .
SRCS = ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strrchr.c ft_strnstr.c ft_strncmp.c \
		ft_memset.c ft_bzero.c ft_memcpy.c ft_memchr.c ft_memcmp.c ft_memmove.c ft_atoi.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c \
		ft_tolower.c ft_calloc.c ft_strchr.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c get_next_line.c ft_itoa_dx.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		ft_atoi_simple.c \
		ft_printf/ft_printf.c\
		ft_printf/print_c.c\
		ft_printf/print_d.c\
		ft_printf/print_s.c\
		ft_printf/print_u.c\
		ft_printf/print_p.c\
		ft_printf/print_xX.c\
		ft_printf/put_num_dx.c\
		strjoin_and_free_null.c \
		strjoin_and_free.c \
		ft_split_triple.c \
		ft_strcmp.c \
		ft_free.c \
		is_str_all_c.c \
		is_last_char_c.c
OBJS = $(SRCS:%.c=%.o)

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

.PHONY: all clean fclean re
