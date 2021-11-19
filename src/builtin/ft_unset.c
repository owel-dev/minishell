/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:36:08 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/19 19:49:31 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **arr_cpy(t_bundle *bundle, t_token *token, \
	char **env_copy, int len)
{
	int i;
	int k;
	char **key;

	i = 0;
	k = 0;
	env_copy[len] = NULL;
	while (bundle->env[i])
	{
		key = ft_split(bundle->env[i], '=');
		if (key == NULL)
			return (NULL);
		if (ft_strcmp(key[0], token->content) != 0)
		{
			env_copy[k] = ft_strdup(bundle->env[i]);
			if (env_copy[k++] == NULL)
			{
				all_free(env_copy);
				all_free(key);
				return (NULL);
			}
		}
		all_free(key);
		i++;
	}
	return (env_copy);
}

int ft_unset(t_bundle *bundle, t_token *token)
{
	char **env_copy;
	int len;

	if (token == NULL || bundle == NULL)
	{
		printf("에러 출력\n");
		return (FAIL);
	}
	len = ft_arrlen(bundle->env);
	if (len == 0)
		return (FAIL);
	if (ft_getenv(bundle, token->content) != NULL)
	{
		env_copy = (char **)malloc(sizeof(char *) * (len + 1));
		if (env_copy == NULL)
			return (NULL);
		env_copy = arr_cpy(bundle, token, env_copy, len);
		if (env_copy == NULL)
			return (FAIL);
		all_free(bundle->env);
		bundle->env = env_copy;
		return (SUCCESS);
	}
	return (FAIL);
}
