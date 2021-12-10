/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:36 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/08 12:59:38 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void append_env(t_bundle *bundle, t_token *token)
{
	int len;
	int i;
	char **env_copy;
	char **temp;

	len = ft_arrlen(bundle->env);
	if (len == 0)
		return ;
	env_copy = (char **)malloc(sizeof(char *) * (len + 2));
	if (env_copy == NULL)
		return ;
	env_copy[len + 1] = NULL;
	env_copy[len] = ft_strdup(token->content);
	i = 0;
	while (i < len)
	{
		env_copy[i] = ft_strdup(bundle->env[i]);
		i++;
	}
	temp = bundle->env;
	bundle->env = env_copy;
	ft_two_free(temp);
}

void replace_env(t_bundle *bundle, t_token *token, char *key)
{
	int i;
	char **env_split;
	char *temp;

	i = 0;
	while (bundle->env[i])
	{
		env_split = ft_split(bundle->env[i], '=');
		if (env_split == NULL)
			return ;
		if (ft_strcmp(env_split[0], key) == 0)
		{
			all_free(env_split);
			temp = bundle->env[i];
			bundle->env[i] = ft_strdup(token->content);
			free(temp);
			return ;
		}
		i++;
	}
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

int valid_argument(t_bundle *bundle)
{
	if (ft_strchr(bundle->token->content, '=') == NULL)
		return (0);
	if (!ft_strncmp(bundle->token->content, "=", 1))
	{
		printf("export: %s: not a valid identifier\n", \
		bundle->token->content);
		return (0);
	}
	return (1);
}

int	builtin_export(t_bundle *bundle)
{
	char	**content_split;
	char	*env_value;
	int		result;

	result = SUCCESS;
	if (bundle->token->next == NULL)
		print_env(bundle);
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
		if (!valid_argument(bundle))
			result = FAIL;
		content_split = ft_split(bundle->token->content, '=');
		if (content_split == NULL)
			result = FAIL;
		env_value = builtin_getenv(bundle, content_split[0]);
		if (env_value)
			replace_env(bundle, bundle->token, content_split[0]);
		else
			append_env(bundle, bundle->token);
		ft_free(env_value);
		all_free(content_split);
	}
	return (result);
}
