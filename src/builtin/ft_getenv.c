/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 03:54:58 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/15 03:54:59 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_getenv(char *key)
{
	int i;
	char **split;
	char *ret;

	i = 0;
	while (g_env[i])
	{
		split = ft_split(g_env[i], '=');
		if (split == NULL)
			return (NULL);
		if (ft_strcmp(split[0], key) == 0)
		{
			ret = ft_strdup(split[1]);
			all_free(split);
			return (ret);
		}
		all_free(split);
		i++;
	}
	return (NULL);
}
