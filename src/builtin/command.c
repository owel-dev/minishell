#include "../minishell.h"

void ft_cd(char *path)
{
	int ret;

	if (path == NULL)
		return ;
	ret = chdir(path);
	if (ret == -1)
		printf("%s\n", strerror(errno));
}

void ft_env(char **env)
{
	int i = 0;

	if (env == NULL || *env == NULL)
		return ;
	while (env[i])
		printf("%s\n", env[i++]);
}

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
	get_env = ft_getenv(key);
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
				all_free(split_env);
				free(g_env[i]);
				g_env[i] = ft_strdup(str);
				return ;
			}
			all_free(split_env);
			i++;
		}
		return ;
	}
	len = 0;
	while (g_env[len])
		len++;
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
	all_free(g_env);
	g_env = env_copy;
}

void ft_pwd(void)
{
	char *ret;
	char s[1000];

	ret = getcwd(s,1000);
	if (ret == 0)
	{
		printf("%s\n", strerror(errno));
		return ;
	}
    printf("%s\n", ret);
}

void ft_unset(char *str)
{
	char **env_copy;
	char **key;
	int i;
	int k;
	int len;

	if (str == NULL)
		return ;
	i = 0;
	while (g_env[i])
		i++;
	len = i;
	if (ft_getenv(str) != NULL)
	{
		env_copy = (char **)malloc(sizeof(char *) * len);
		if (env_copy == NULL)
			return ;
		env_copy[len] = NULL;
		i = 0;
		k = 0;
		while (g_env[i])
		{
			key = ft_split(g_env[i], '=');
			if (ft_strcmp(key[0], str) != 0)
			{
				env_copy[k] = g_env[i];
				k++;
			}
			all_free(key);
			i++;
		}
		free(g_env);
		g_env = env_copy;
	}
}
