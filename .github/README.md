# minishell

## Description
minishell is a very simple shell written in C.
It has the following commands built in.

- echo
- cd
- pwd
- export
- unset
- env
- exit

## Requirement
- OS X
- C compiler
- make
- readline

To install readline on a mac, use brew, etc. as follows.

``` sh
brew install readline
```

## Build
Execute the following command in the appropriate directory.

``` sh
https://github.com/Yamada-Ika/minishell.git
cd minishell
make
```

## Usage
Execute the following command in the directory where `minishell` exists.
After execution, a prompt will appear.

``` sh
./minishell
minishell>
```

## Features
- It reproduces the following basic behaviors
  - Pipes, redirects, and heredocs
  - Environment variable registration, deletion, and variable expansion

- example

``` sh
minishell> echo aaa | cat | cat | cat | cat
aaa
minishell> cat Makefile > log
minishell> diff log Makefile | cat -e
minishell>
```

``` sh
minishell> cat << EOS
> hoge
> EOS
hoge
```

``` sh
minishell> export test=hoge
minishell> echo $test
hoge
minishell> unset test
minishell> echo $test

minishell>
```

- `\`, `;`, and so on cannot be interpreted!

## Author
@shige-lab

## Licence
This software is released under the MIT License, see LICENSE.
