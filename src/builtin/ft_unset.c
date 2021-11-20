/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:36:08 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/20 19:19:59 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **arr_cpy(t_bundle *bundle, t_token *token, int len)
{
	int i;
	int k;
	char **key;
	char **env_copy;

	i = 0;
	k = 0;
	env_copy = (char **)malloc(sizeof(char *) * len);
	if (env_copy == NULL)
		return (NULL);
	env_copy[len - 1] = NULL;
	while (bundle->env[i])
	{
		key = ft_split(bundle->env[i], '=');
		if (key == NULL)
			return (NULL);
		if (ft_strcmp(key[0], token->content) != 0)
		{
			env_copy[k] = ft_strdup(bundle->env[i]);
			k++;
		}
		i++;
		all_free(key);
	}
	return (env_copy);
}

int ft_unset(t_bundle *bundle)
{
	char **env_copy;
	int len;

	if (bundle == NULL || bundle->token == NULL)
	{
		printf("not enough argument\n");
		return (FAIL);
	}
	bundle->token = bundle->token->next;
	while (bundle->token && bundle->token->token_type != PIPE)
	{
		len = ft_arrlen(bundle->env);
		if (len == 0)
			return (FAIL);
		if (ft_getenv(bundle, bundle->token->content) != NULL)
		{
			env_copy = arr_cpy(bundle, bundle->token, len);
			if (env_copy == NULL)
				return (FAIL);
			all_free(bundle->env);
			bundle->env = env_copy;
		}
		bundle->token = bundle->token->next;
	}
	return (SUCCESS);
}
