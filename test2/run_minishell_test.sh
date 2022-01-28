#!/bin/bash

out_dir="$(pwd)"

function TAKE_LOG_FAILE_TEST() {
	test_case="$1"
	msh_file="$2"
	bash_file="$3"
	echo $msh_file $bash_file
	echo "===============================================================" >> $out_dir/faile.log
	echo "test case : $test_case" >> $out_dir/faile.log
	echo "------------------------- diff result -------------------------" >> $out_dir/faile.log
	diff -a -u $msh_file $bash_file >> $out_dir/faile.log
	echo "---------------------- minishell result -----------------------" >> $out_dir/faile.log
	cat $msh_file >> $out_dir/faile.log
	echo "------------------------- bash result -------------------------" >> $out_dir/faile.log
	cat $bash_file >> $out_dir/faile.log
	echo "===============================================================" >> $out_dir/faile.log
}

function IS_SAME_FILE() {
	file_1="$1"
	file_2="$2"
	diff $file_1 $file_2 > $out_dir/out.diff
	size=$(ls -l $out_dir/out.diff | awk '{print $5}')
	if [ $size -eq 0 ]
	then
		return 0
	else
		return 1
	fi
}

function CLEAN_TEST_DIR() {
	rm -rf *.txt
	rm -rf $(pwd)"/dir"
}

function TEST() {
	test_case="$1"
	echo "test_case : $test_case"
	echo -n "$test_case" > $out_dir/msh.in
	echo " > $out_dir/msh.out" >> $out_dir/msh.in
	if [ $(uname) = "Linux" ]
	then
    valgrind --leak-check=full ../minishell < $out_dir/msh.in 2> tmp.log
    flag=$(cat tmp.log | awk '$2=="definitely" {if ($4 != 0) print $4}')
    if [ $flag -ne 0 ]
    then
      cat tmp.log >> ../valgrind.log
    fi
  else
    ../minishell < $out_dir/msh.in
	fi
	CLEAN_TEST_DIR
	echo -n "$test_case" > $out_dir/bash.in
	echo " > $out_dir/bash.out" >> $out_dir/bash.in
	bash < $out_dir/bash.in
	CLEAN_TEST_DIR
	IS_SAME_FILE $out_dir/msh.out $out_dir/bash.out
	if [ $? -eq 0 ]
	then
		echo -e "\n\033[32m$test_case : OK!\033[m"
	else
		echo -e "\n\033[31m$test_case : KO!\033[m"
		TAKE_LOG_FAILE_TEST "$test_case" $out_dir/msh.out $out_dir/bash.out
		export TEST_STATUS=1
	fi
}

function READ_TESTCASE() {
	while read test_case
	do
		hoge=$(echo $test_case | tr ';' '\n')
		TEST "$hoge"
	done
}

bash clean_test_files.sh
mkdir "../test_dir"
cd ../test_dir

#export TEST_STATUS=0

# READ_TESTCASE < ../test2/cases/cd.txt
#READ_TESTCASE < ../test2/cases/echo.txt
#READ_TESTCASE < ../test2/cases/env.txt
#READ_TESTCASE < ../test2/cases/exit.txt
READ_TESTCASE < ../test2/cases/expand.txt
READ_TESTCASE < ../test2/cases/export.txt
READ_TESTCASE < ../test2/cases/simple_command.txt
#READ_TESTCASE < ../test2/cases/path.txt
#READ_TESTCASE < ../test2/cases/syntax_error.txt
#READ_TESTCASE < ../test2/cases/pwd.txt
#READ_TESTCASE < ../test2/cases/unset.txt
#READ_TESTCASE < ../test2/cases/redirect.txt
#READ_TESTCASE < ../test2/cases/shlvl.txt
#READ_TESTCASE < ../test2/cases/added_test.txt

cd ..
rm -rf test_dir
exit 0

# exit status
TEST \
"
echo
echo \$?"

TEST \
"
echo 42tokyo
echo \$?"

TEST \
"
echo 4 2 T o k y o
echo \$?"

TEST \
"
echo -n 42tokyo
echo \$?"

TEST \
"
echo -n echo fourty two FOURTY TWO
echo \$?"

TEST \
"
cd ../
echo \$?"

TEST \
"
cd hoge
echo \$?"

TEST \
"
cd
echo \$?"

TEST \
"
pwd
echo \$?"

# Simple command
TEST "/bin/ls"
TEST "/bin/pwd"
TEST "/bin/echo 42tokyo"

# Count global variables
global_val_count=$(cat $(find ./ -name "*.c" -or -name "*.h" | grep -v libft) | grep "\t\**g_[a-zA-Z]*;" | wc -l)
if [ $global_val_count -eq 0 ]
then
	echo -e "\n\033[32m global variable check : OK!\033[m"
else
	echo -e "\n\033[31m global variable check : KO!\033[m"
	export TEST_STATUS=1
fi

TEST " "
TEST "  "
TEST "   "
TEST "    "
TEST "     "
TEST "      "
TEST "	"
TEST "		"
TEST "			"
TEST "				"
TEST "					"

# Arguments
TEST "/bin/ls -a"
# TEST "/bin/ls -l"
TEST "/bin/pwd"
TEST "/bin/echo -n 42tokyo"

# test_case=$(cat << EOS
# /bin/pwd
# /bin/ls
# EOS
# )

TEST \
"/bin/ls -a
/bin/ls -l
/bin/pwd
/bin/echo -n 42tokyo"

# echo
TEST "echo"
TEST "echo -n 42"
TEST "echo -nn 42"
TEST "echo -nnnnnnnnnnnnn 42"
TEST "echo -nnk 42"
TEST "echo -nkn 42"
TEST "echo 42"
TEST "echo \"42\""
TEST "echo '42'"
TEST "echo Tokyo\"42\""
TEST "echo Tokyo'42'"
TEST "echo \"42\"Tokyo"
TEST "echo '42'Tokyo"
TEST "echo Paris\"42\"Tokyo"
TEST "echo -n 42"
TEST "echo -n \"42\""
TEST "echo -n '42'"
TEST "echo -n Tokyo\"42\""
TEST "echo -n Tokyo'42'"
TEST "echo -n \"42\"Tokyo"
TEST "echo -n '42'Tokyo"
TEST "echo -n Paris\"42\"Tokyo"

# double quotes
TEST "echo \" 42 \""
TEST "echo \"  Tokyo \""
TEST "echo \"   Paris  \""
TEST "echo \"    Codam   \""
TEST "echo \"cat lol.c | cat > lol.c\""
TEST "echo \"\$PATH\""
TEST "echo \"\$USER\""
TEST "echo \"\$LANG\""

# single quotes
TEST "echo ' 42 '"
TEST "echo '  Tokyo '"
TEST "echo '   Paris  '"
TEST "echo '    Codam   '"
TEST "echo 'cat lol.c | cat > lol.c << EOF > res.log'"
TEST "echo '\$PATH'"
TEST "echo '\$USER'"
TEST "echo '\$LANG'"

# env
TEST "env | sort"
TEST \
"export key=value
env | sort"
TEST \
"export TEST1=\"42Tokyo\"
export TEST2=\"42 Tokyo\"
export TEST3=\" 42 Tokyo\"
export TEST4=\" 42 Tokyo \"
export TEST5=' 42 Tokyo '
export TEST6=''
export TEST7=\"\"
export TEST8=
export TEST9
env | sort"

# export
TEST "export | sort"
TEST \
"export key=value
export | sort"
TEST \
"export TEST1=\"42Tokyo\"
export TEST2=\"42 Tokyo\"
export TEST3=\" 42 Tokyo\"
export TEST4=\" 42 Tokyo \"
export TEST5=' 42 Tokyo '
export TEST6=''
export TEST7=\"\"
export TEST8=
export TEST9
export | sort"

# pwd
TEST "pwd"
TEST \
"cd ..
pwd
cd ..
pwd
cd ..
pwd"

# relative path
TEST "cd libft | wc -l"

# path
TEST "ls"
TEST "ls | wc -l"
TEST "ls | awk '{print \$5}'"

# redirection
# TEST "cat < main.c > file1"

# pipe
TEST "cat main.c | grep int"

# crasy
TEST "dsbksdgbksdghsd"

# environment variables
TEST "echo \$PATH"
TEST "echo \"\$USER\""

# echo & ft_pipe
TEST "echo 42 | cat"
TEST "echo 42 | cat"
TEST "echo \"42\" | cat"
TEST "echo '42' | cat"
TEST "echo Tokyo\"42\" | cat"
TEST "echo Tokyo'42' | cat"
TEST "echo \"42\"Tokyo | cat"
TEST "echo '42'Tokyo | cat"
TEST "echo Paris\"42\"Tokyo | cat"

# echo & multi-ft_pipe
TEST "echo 42 | cat | cat"
TEST "echo 42 | cat | cat"
TEST "echo \"42\" | cat | cat"
TEST "echo '42' | cat | cat"
TEST "echo Tokyo\"42\" | cat | cat"
TEST "echo Tokyo'42' | cat | cat"
TEST "echo \"42\"Tokyo | cat | cat"
TEST "echo '42'Tokyo | cat | cat"
TEST "echo Paris\"42\"Tokyo | cat | cat"
TEST "echo 42 | cat | cat | cat"
TEST "echo 42 | cat | cat | cat"
TEST "echo \"42\" | cat | cat | cat"
TEST "echo '42' | cat | cat | cat"
TEST "echo Tokyo\"42\" | cat | cat | cat"
TEST "echo Tokyo'42' | cat | cat | cat"
TEST "echo \"42\"Tokyo | cat | cat | cat"
TEST "echo '42'Tokyo | cat | cat | cat"
TEST "echo Paris\"42\"Tokyo | cat | cat | cat"

if [ $TEST_STATUS -eq 0 ]
then
	echo -e "\033[32mAll test : OK!\033[m"
else
	echo -e "\033[31mSome test : KO!\033[m"
fi
