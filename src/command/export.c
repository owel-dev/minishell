#include "../minishell.h"

void ft_export(char *str)
{
	char **split_str;
	char *key;
	char **env_copy;
	char *get_env;
	char **split_env;
	int len;
	int i;

	if (str == NULL || ft_strchr(str, '=') == NULL)
		return ;

	split_str = ft_split(str, '=');
	if (split_str == NULL)
		return ;
	key = split_str[0];
	get_env = getenv(key);
	if (get_env != NULL)
	{
		i = 0;
		while (g_env[i])
		{
			split_env = ft_split(g_env[i], '=');
			if (split_env == NULL)
				return ;
			if (ft_strcmp(split_env[0], key) == 0)
			{
				free_two(split_env);
				free(g_env[i]);
				g_env[i] = ft_strdup(str);
				return ;
			}
			free_two(split_env);
			i++;
		}
		return ;
	}

	len = 0;
	while (g_env[len])
		len++;
	// printf("%d\n", len);
	env_copy = (char **)malloc(sizeof(char *) * len + 2);
	if (env_copy == NULL)
		return ;
	env_copy[len + 1] = NULL;
	env_copy[len] = str;
	i = 0;
	while (i < len)
	{
		env_copy[i] = ft_strdup(g_env[i]);
		i++;
	}
	free_two(g_env);
	g_env = env_copy;
	return ;
}
