#!/bin/bash

if [ "$1" = "1" ]
then
	ARG="ALL"
elif [ "$1" = "2" ]
then
	ARG="TOKEN"
elif [ "$1" = "3" ]
then
	ARG="PARSE"
else
	ARG="EXPAND"
fi
#LDFLAGS="-lreadline -lhistory -L$(brew --prefix readline)/lib"
INCLUDE="-I ../include"
#LDFLAGS="-lreadline -lhistory -L$(brew --prefix readline)/lib"
#INCLUDE="-I ../include -I$(brew --prefix readline)/include -Iinclude"
echo "$2" >> log.log
gcc $INCLUDE -D$ARG -o debug ../src/parse.c ../src/expansion.c ../src/lexer.c ../src/utils.c ../src/free.c \
 ../src/here_doc.c  ../src/handle_token_in_quotes.c ../src/create_t_command.c *.c ../libft/libft.a && ./debug $2 1>> log.log
#gcc $INCLUDE $LDFLAGS -D$ARG -o debug ../src/*.c *.c ../libft/libft.a && ./debug $2 1>> log.log
#rm -rf debug
