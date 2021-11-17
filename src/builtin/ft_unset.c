/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:36:08 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/17 16:36:09 by hyospark         ###   ########.fr       */
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
