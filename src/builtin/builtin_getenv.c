/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 03:54:58 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/08 12:56:15 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *builtin_getenv(t_bundle *bundle, char *key)
{
	int i;
	char *ret;
	char *equal;
	char *env_key;
	char *env_value;

	if (key[1] == '?')
		return (ft_itoa(g_status));
	i = 0;
	while (bundle->env[i])
	{
		equal = ft_strchr(bundle->env[i], '=');
		env_key = ft_substr(bundle->env[i], 0, equal - bundle->env[i]);
		env_value = equal + 1;
		if (*env_value == '\0')
			env_value = "";
		if (ft_strcmp(env_key, key) == 0)
		{
			ft_free(env_key);
			return (ft_strdup(env_value));
		}
		ft_free(env_key);
		i++;
	}
	return (NULL);
}
