#include "minishell.h"


static size_t	_get_strs_len(char const **s, char *c)
{
	size_t	strs_len;
	size_t	i;

	strs_len = 0;
	i = 0;
	while (s[i] != NULL)
	{
		if (ft_strncmp(s[i], c, ft_strlen(c)) == 0 || *(s + 1) == NULL)
			strs_len++;
		i++;
	}
	return (strs_len);
}

static size_t	_get_str_len(char const **s, char *c)
{
	size_t	str_len;

	str_len = 0;
	while (*s != NULL && ft_strncmp(*s, c, ft_strlen(c)))
	{
		str_len++;
		s++;
	}
	return (str_len);
}

static char	**_get_str(char const **s, size_t str_len)
{
	char **strs;
	size_t	i;

	i = 0;
	strs = (char **)ft_calloc((str_len + 1), sizeof(char *));
	if (strs == NULL)
		return (NULL);
	while (i < str_len)
	{
		strs[i] = ft_strdup(s[i]);
		i++;
	}
	// printf("47  %s\n", strs[0]);
	return (strs);
}

static bool	_get_strs_recursive(char ***strs, char const **s, char *c)
{
	size_t	str_len;

	if (*s && ft_strncmp(*s, c, ft_strlen(c)) == 0)
		s++;
	// printf("%s\n",*s);
	if (*s == NULL)
	{
		*strs = NULL;
		return (true);
	}
	str_len = _get_str_len(s, c);
	// printf("%zu\n",str_len);
	*strs = _get_str(s, str_len);
	// printf("72  %s\n", *strs[0]);
	if (*strs == NULL)
		return (false);
	if (!_get_strs_recursive(strs + 1, s + str_len, c))
	{
		// free(*strs);
		return (false);
	}
	return (true);
}



char	***ft_split_triple(char const **strs, char *sets)
{
	char	***triple;
	size_t	strs_len;

	if (strs == NULL)
		return (NULL);
	strs_len = _get_strs_len(strs, sets);
	// printf("%zu\n",strs_len);
	triple = (char ***)ft_calloc(sizeof(char **), (strs_len + 2));
	if (triple == NULL)
		return (NULL);
	if (!_get_strs_recursive(triple, strs, sets))
	{
		// free(strs);
		return (NULL);
	}
	return (triple);
}

// int main(int ac, char **ar)
// {
// 	char ***test = ft_split_triple(ar + 1, "|");
// 	printf("--------------------------------\n");
// 	for (size_t i = 0; i < 100; i++)
// 	{
// 		if (!test[i])
// 			break;
// 		for (size_t j = 0; j < 100; j++)
// 		{
// 			if (!test[i][j])
// 				break;
// 			printf("%s\n", test[i][j]);
// 		}
// 	}
// }