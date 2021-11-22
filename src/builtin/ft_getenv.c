/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 03:54:58 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/22 20:10:44 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_getenv(t_bundle *bundle, char *key)
{
	int i;
	char *ret;
	char *equal;
	char *env_key;
	char *env_value;

	i = 0;
	while (bundle->env[i])
	{
		equal = ft_strchr(bundle->env[i], '=');
		env_key = ft_substr(bundle->env[i], 0, equal - bundle->env[i]);
		env_value = ++equal;
		if (*env_value == '\0')
			env_value = "";
		if (ft_strcmp(env_key, key) == 0)
		{
			free(env_key);
			ret = ft_strdup(env_value);
			if (ret == NULL)
				return (NULL);
			return (ret);
		}
		i++;
	}
	return (NULL);
}
