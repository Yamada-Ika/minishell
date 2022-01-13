# test case

## parse error case
| cat
cat | ls |

## signal

```
# CTRL-C
minishell> ^C
minishell>

minishell> cat
^C
minishell>

minishell> cat
^\
minishell> 

# CTRL-D
minishell>

# catの後にCTRL-Cして、そのあともう一度CTRL-Cするとうまく行かない
minishell> cat
^C
minishell> ^C
```