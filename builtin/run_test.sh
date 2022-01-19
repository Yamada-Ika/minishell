#!/bin/bash

test_cmd_name="$1"

if [ $test_cmd_name = "env" ]
then
	SRCS="env_test.c env.c export.c envvar_utils.c"
elif [ $test_cmd_name = "export" ]
then
	SRCS="export_test.c export.c env.c envvar_utils.c"
elif [ $test_cmd_name = "unset" ]
then
	SRCS="unset_test.c unset.c export.c env.c envvar_utils.c"
elif [ $test_cmd_name = "getenv" ]
then
	SRCS="my_getenv_test.c my_getenv.c export.c env.c inherite_env_val.c envvar_utils.c"
elif [ $test_cmd_name = "echo" ]
then
	SRCS="echo_test.c echo.c"
elif [ $test_cmd_name = "inherite" ]
then
	SRCS="inherite_env_val_test.c inherite_env_val.c env.c export.c envvar_utils.c"
fi

gcc $SRCS -o test -I../libft ../libft/libft.a
./test
rm -rf ./test
