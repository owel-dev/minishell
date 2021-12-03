/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:36 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/03 17:48:50 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int append_env(t_bundle *bundle, t_token *token)
{
	int len;
	int i;
	char **env_copy;

	len = ft_arrlen(bundle->env);
	if (len == 0)
		return (FAIL);
	env_copy = (char **)malloc(sizeof(char *) * (len + 2));
	if (env_copy == NULL)
		return (FAIL);
	env_copy[len + 1] = NULL;
	env_copy[len] = ft_strdup(token->content);
	i = 0;
	while (i < len)
	{
		env_copy[i] = ft_strdup(bundle->env[i]);
		i++;
	}
	bundle->env = env_copy;
	return (SUCCESS);
}

int replace_env(t_bundle *bundle, t_token *token, char *key)
{
	int i;
	char **env_split;

	i = 0;
	while (bundle->env[i])
	{
		env_split = ft_split(bundle->env[i], '=');
		if (env_split == NULL)
			return (FAIL);
		if (ft_strcmp(env_split[0], key) == 0)
		{
			all_free(env_split);
			free(bundle->env[i]);
			bundle->env[i] = ft_strdup(token->content);
			return (SUCCESS);
		}
		// all_free(env_split);
		i++;
	}
	return (FAIL);
}

void print_env(t_bundle *bundle)
{
	int i;
	char *env_line;

	i = 0;
	while (bundle->env[i])
	{
		env_line = ft_strjoin("declare -x ", bundle->env[i]);
		printf("%s\n", env_line);
		free(env_line);
		i++;
	}
}

int	ft_export(t_bundle *bundle)
{
	char	**content_split;
	char	*value;
	int		result;
	if (bundle->token->next == NULL)
	{
		print_env(bundle);
		return (SUCCESS);
	}
	result = SUCCESS;
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
		if (!ft_strncmp(bundle->token->content, "=", 1))
		{
			printf("export: %s: not a valid identifier\n", \
			bundle->token->content);
			continue ;
		}
		if (ft_strchr(bundle->token->content, '=') == NULL)
			continue ;
		content_split = ft_split(bundle->token->content, '=');
		if (content_split == NULL)
			return (FAIL);
		value = ft_getenv(bundle, content_split[0]);
		if (value)
			result = replace_env(bundle, bundle->token, content_split[0]);
		else
			result = append_env(bundle, bundle->token);
		all_free(content_split);
	}
	return (result);
}
