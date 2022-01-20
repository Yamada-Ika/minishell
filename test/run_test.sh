#!/bin/bash

function BUILTIN_TEST() {
	test_cmd_name="$1"

	if [ $test_cmd_name = "env" ]
	then
		SRCS="env_test.c"
	elif [ $test_cmd_name = "export" ]
	then
		SRCS="export_test.c"
	elif [ $test_cmd_name = "unset" ]
	then
		SRCS="unset_test.c"
	elif [ $test_cmd_name = "getenv" ]
	then
		SRCS="my_getenv_test.c"
	elif [ $test_cmd_name = "echo" ]
	then
		SRCS="echo_test.c"
	elif [ $test_cmd_name = "inherite" ]
	then
		SRCS="inherite_env_val_test.c"
	fi

	gcc $SRCS ../builtin/*.c -o test -I../libft ../libft/libft.a -I../include -I../builtin
	./test
}

BUILTIN_TEST "env"
BUILTIN_TEST "export"
BUILTIN_TEST "unset"
BUILTIN_TEST "getenv"
BUILTIN_TEST "echo"
BUILTIN_TEST "inherite"

rm -rf ./test
