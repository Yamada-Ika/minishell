#!/bin/bash

function TAKE_LOG_FAILE_TEST() {
	test_case="$1"
	msh_file="$2"
	bash_file="$3"
	echo $msh_file $bash_file
	echo "===============================================================" >> test2/faile.log
	echo "test case : $test_case" >> test2/faile.log
	echo "---------------------- minishell result -----------------------" >> test2/faile.log
	cat $msh_file >> test2/faile.log
	echo "------------------------- bash result -------------------------" >> test2/faile.log
	cat $bash_file >> test2/faile.log
	echo "===============================================================" >> test2/faile.log
}

function IS_SAME_FILE() {
	file_1="$1"
	file_2="$2"
	diff $file_1 $file_2 > test2/out.diff
	size=$(ls -l test2/out.diff | awk '{print $5}')
	if [ $size -eq 0 ]
	then
		return 0
	else
		return 1
	fi
}

function STDOUT_TEST() {
	test_case="$1"
	echo -n "$test_case" > test2/msh.in
	echo " > test2/msh.out" >> test2/msh.in
	./minishell < test2/msh.in
	echo -n "$test_case" > test2/bash.in
	echo " > test2/bash.out" >> test2/bash.in
	bash < test2/bash.in
	IS_SAME_FILE test2/msh.out test2/bash.out
	if [ $? -eq 0 ]
	then
		echo -e "\n\033[32m$test_case : OK!\033[m"
	else
		echo -e "\n\033[31m$test_case : KO!\033[m"
		TAKE_LOG_FAILE_TEST "$test_case" test2/msh.out test2/bash.out
	fi
}

rm -rf faile.log
cd ../

STDOUT_TEST "echo \$PATH"
exit 0

# Simple command
STDOUT_TEST "/bin/ls"
STDOUT_TEST "/bin/pwd"
STDOUT_TEST "/bin/echo 42tokyo"

# Count global variables
global_val_count=$(cat $(find ./ -name "*.c" -or -name "*.h" | grep -v libft) | grep "\t\**g_[a-zA-Z]*;" | wc -l)
if [ $global_val_count -eq 0 ]
then
	echo -e "\n\033[32m global variable check : OK!\033[m"
else
	echo -e "\n\033[31m global variable check : KO!\033[m"
fi

STDOUT_TEST " "
STDOUT_TEST "  "
STDOUT_TEST "   "
STDOUT_TEST "    "
STDOUT_TEST "     "
STDOUT_TEST "      "
STDOUT_TEST "	"
STDOUT_TEST "		"
STDOUT_TEST "			"
STDOUT_TEST "				"
STDOUT_TEST "					"

# Arguments
STDOUT_TEST "/bin/ls -a"
STDOUT_TEST "/bin/ls -l"
STDOUT_TEST "/bin/pwd"
STDOUT_TEST "/bin/echo -n 42tokyo"

# test_case=$(cat << EOS
# /bin/pwd
# /bin/ls
# EOS
# )

STDOUT_TEST \
"/bin/ls -a
/bin/ls -l
/bin/pwd
/bin/echo -n 42tokyo"

# echo
STDOUT_TEST "echo"
STDOUT_TEST "echo 42"
STDOUT_TEST "echo \"42\""
STDOUT_TEST "echo '42'"
STDOUT_TEST "echo Tokyo\"42\""
STDOUT_TEST "echo Tokyo'42'"
STDOUT_TEST "echo \"42\"Tokyo"
STDOUT_TEST "echo '42'Tokyo"
STDOUT_TEST "echo Paris\"42\"Tokyo"
STDOUT_TEST "echo -n 42"
STDOUT_TEST "echo -n \"42\""
STDOUT_TEST "echo -n '42'"
STDOUT_TEST "echo -n Tokyo\"42\""
STDOUT_TEST "echo -n Tokyo'42'"
STDOUT_TEST "echo -n \"42\"Tokyo"
STDOUT_TEST "echo -n '42'Tokyo"
STDOUT_TEST "echo -n Paris\"42\"Tokyo"

# double quotes
STDOUT_TEST "echo \" 42 \""
STDOUT_TEST "echo \"  Tokyo \""
STDOUT_TEST "echo \"   Paris  \""
STDOUT_TEST "echo \"    Codam   \""
STDOUT_TEST "echo \"cat lol.c | cat > lol.c\""
STDOUT_TEST "echo \"\$PATH\""
STDOUT_TEST "echo \"\$USER\""
STDOUT_TEST "echo \"\$LANG\""

# single quotes
STDOUT_TEST "echo ' 42 '"
STDOUT_TEST "echo '  Tokyo '"
STDOUT_TEST "echo '   Paris  '"
STDOUT_TEST "echo '    Codam   '"
STDOUT_TEST "echo 'cat lol.c | cat > lol.c << EOF > res.log'"
STDOUT_TEST "echo '\$PATH'"
STDOUT_TEST "echo '\$USER'"
STDOUT_TEST "echo '\$LANG'"

# env
STDOUT_TEST "env"

# export
STDOUT_TEST "export"
STDOUT_TEST "export hoge=hogeeeeeei"
STDOUT_TEST "export hoge=hugahuga"

# pwd
STDOUT_TEST "pwd"
STDOUT_TEST \
"cd ..
pwd
cd ..
pwd
cd ..
pwd"

# relative path
STDOUT_TEST "cd libft | wc -l"

# path
STDOUT_TEST "ls"
STDOUT_TEST "ls | wc -l"
STDOUT_TEST "ls | awk '{print \$5}'"

# redirection
# STDOUT_TEST "cat < main.c > file1"

# pipe
STDOUT_TEST "cat main.c | grep int"

# crasy
STDOUT_TEST "dsbksdgbksdghsd"
STDOUT_TEST "cat | cat | ls"

# environment variables
STDOUT_TEST "echo \$PATH"
STDOUT_TEST "echo \"\$USER\""

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

echo -e "\033[32mAll test : OK!\033[m"
