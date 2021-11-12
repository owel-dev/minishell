/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:11:49 by ulee              #+#    #+#             */
/*   Updated: 2021/11/12 11:11:49 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_unset(char *str)
{
	char **env_copy;
	char **key;
	int i;
	int k;
	int len;

	i = 0;
	while (g_env[i])
		i++;
	len = i;
	if (getenv(str) != NULL)
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
			free_two(key);
			i++;
		}
		free(g_env);
		g_env = env_copy;
	}
}
