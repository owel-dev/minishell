/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:36 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/20 19:44:27 by hyospark         ###   ########.fr       */
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
	env_copy = (char **)malloc(sizeof(char *) * len + 2);
	if (env_copy == NULL)
		return (FAIL);
	env_copy[len + 1] = NULL;
	env_copy[len] = token->content;
	i = 0;
	while (i < len)
	{
		env_copy[i] = ft_strdup(bundle->env[i]);
		i++;
	}
	all_free(bundle->env);
	bundle->env = env_copy;
	return (SUCCESS);
}

int replace_env(t_bundle *bundle, t_token *token, char *key)
{
	int i;
	char **env_split;

	if (bundle == NULL || token == NULL || key == NULL)
		return (FAIL);
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
		all_free(env_split);
		i++;
	}
	return (FAIL);
}

int ft_export(t_bundle *bundle)
{
	char **content_split;
	char *key;
	char *value;
	int result;

	if (bundle == NULL || bundle->token == NULL)
		return (FAIL);
	if (ft_strchr(bundle->token->next->content, '=') == NULL)
		return (FAIL);
	content_split = ft_split(bundle->token->next->content, '=');
	if (content_split == NULL)
		return (FAIL);
	key = content_split[0];
	value = ft_getenv(bundle, key);
	if (value)
		result = replace_env(bundle, bundle->token->next, key);
	else
		result = append_env(bundle, bundle->token->next);
	while (bundle->token && bundle->token->token_type != PIPE)
		bundle->token = bundle->token->next;
	return (result);
}
