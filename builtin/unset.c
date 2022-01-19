#include "envvar.h"

void	unset(t_envvar **envs, char *key)
{
	t_envvar	*head;
	t_envvar	*cur;
	t_envvar	*prev;
	size_t		key_len;

	head = *envs;
	prev = NULL;
	key_len = strlen(key);
	while (*envs != NULL)
	{
		if (strcmp((*envs)->key, key) == 0)
		{
			delete_envvar_contents((*envs)->key, (*envs)->val);
			cur = *envs;
			(*envs) = cur->next;
			if (prev != NULL)
				prev->next = cur->next;
			else
				head = cur->next;
			free(cur);
			break ;
		}
		prev = *envs;
		*envs = (*envs)->next;
	}
	*envs = head;
}
