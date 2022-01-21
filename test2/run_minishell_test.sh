#!/bin/bash

function IS_SAME_FILE() {
	file_1="$1"
	file_2="$2"
	diff $file_1 $file_2 > out.diff
	size=$(ls -l out.diff | awk '{print $5}')
	if [ $size -eq 0 ]
	then
		return 0
	else
		return 1
	fi
}

function STDOUT_TEST() {
	test_case="$1"

	echo -n $test_case > msh.in
	echo " > msh.out" >> msh.in
	../minishell < msh.in
	echo -n $test_case > bash.in
	echo " > bash.out" >> bash.in
	bash < bash.in
	IS_SAME_FILE msh.out bash.out
	if [ $? -eq 0 ]
	then
		echo -e "\n\033[32m$test_case : OK!\033[m"
	else
		echo -e "\n\033[31m$test_case : KO!\033[m"
		exit 1
	fi
}

# echo
STDOUT_TEST "echo 42"
STDOUT_TEST "echo \"42\""
STDOUT_TEST "echo '42'"
STDOUT_TEST "echo Tokyo\"42\""
STDOUT_TEST "echo Tokyo'42'"
STDOUT_TEST "echo \"42\"Tokyo"
STDOUT_TEST "echo '42'Tokyo"
STDOUT_TEST "echo Paris\"42\"Tokyo"

# echo & pipe
STDOUT_TEST "echo 42 | cat"
STDOUT_TEST "echo 42 | cat"
STDOUT_TEST "echo \"42\" | cat"
STDOUT_TEST "echo '42' | cat"
STDOUT_TEST "echo Tokyo\"42\" | cat"
STDOUT_TEST "echo Tokyo'42' | cat"
STDOUT_TEST "echo \"42\"Tokyo | cat"
STDOUT_TEST "echo '42'Tokyo | cat"
STDOUT_TEST "echo Paris\"42\"Tokyo | cat"

# echo & multi-pipe
STDOUT_TEST "echo 42 | cat | cat"
STDOUT_TEST "echo 42 | cat | cat"
STDOUT_TEST "echo \"42\" | cat | cat"
STDOUT_TEST "echo '42' | cat | cat"
STDOUT_TEST "echo Tokyo\"42\" | cat | cat"
STDOUT_TEST "echo Tokyo'42' | cat | cat"
STDOUT_TEST "echo \"42\"Tokyo | cat | cat"
STDOUT_TEST "echo '42'Tokyo | cat | cat"
STDOUT_TEST "echo Paris\"42\"Tokyo | cat | cat"
STDOUT_TEST "echo 42 | cat | cat | cat"
STDOUT_TEST "echo 42 | cat | cat | cat"
STDOUT_TEST "echo \"42\" | cat | cat | cat"
STDOUT_TEST "echo '42' | cat | cat | cat"
STDOUT_TEST "echo Tokyo\"42\" | cat | cat | cat"
STDOUT_TEST "echo Tokyo'42' | cat | cat | cat"
STDOUT_TEST "echo \"42\"Tokyo | cat | cat | cat"
STDOUT_TEST "echo '42'Tokyo | cat | cat | cat"
STDOUT_TEST "echo Paris\"42\"Tokyo | cat | cat | cat"

echo "OK!"
