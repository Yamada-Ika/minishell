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
fi

gcc $SRCS -o test
./test
rm -rf ./test
