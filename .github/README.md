# EBNF

```
command_line = command ( "|" command )*
command = redirection? word_list redirection?
redirection = ( "<" | "<<" | ">" | ">>" )? word
word_list = word word*
```
