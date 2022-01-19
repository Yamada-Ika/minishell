#include "test.h"

int	main(void)
{
	t_envvar	*env1;
	char		*key[10];
	char		*val[10];

	key[0] = strdup("key");
	val[0] = strdup("val");
	env1 = new_envlist(key[0], val[0]);
	assert(strcmp(env1->key, key[0]) == 0);
	assert(strcmp(env1->val, val[0]) == 0);
	assert(env1->next == NULL);

	key[1] = strdup("hoge");
	val[1] = strdup("hugaaaaa");
	add_envlist(env1, new_envlist(key[1], val[1]));
	assert(strcmp(env1->key, key[0]) == 0);
	assert(strcmp(env1->val, val[0]) == 0);
	assert(strcmp(env1->next->key, key[1]) == 0);
	assert(strcmp(env1->next->val, val[1]) == 0);
	assert(env1->next->next == NULL);

	delete_envlists(env1);
}
