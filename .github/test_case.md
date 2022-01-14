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

## 環境変数展開

できてる
./minishell "qqqqq | ls -l fff | cat \$hoge aaaa"

- 環境変数が存在しないケース
```
./minishell "\$bbbb"

parse: =========================================
word_list_size 2 word_list->str $
word_list-str:  
expansion: =========================================
word_list_size 0 word_list->str 
```

できてない
```
% ./minishell "\$hoge"

parse: =========================================
word_list_size 2 word_list->str $
ffff fowefow wwwwee 0229393
count : 4
word_list-str:  $
expansion: =========================================
word_list_size 4 word_list->str $
```

## メモ
- 環境変数が入れ子みたいになってる時、展開する必要があるけどやるか迷う
```
% export hoge="$LANG"
% echo $hoge
ja_JP.UTF-8
```
