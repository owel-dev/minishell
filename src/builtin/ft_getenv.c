/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 03:54:58 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/20 23:16:51 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_getenv(t_bundle *bundle, char *key)
{
	int i;
	char **split;
	char *ret;

	i = 0;
	while (bundle->env[i])
	{
		split = ft_split(bundle->env[i], '=');
		if (split == NULL)
			return (NULL);
		if (ft_strcmp(split[0], key) == 0)
		{
			ret = ft_strdup(split[1]);
			all_free(split);
			if (ret == NULL)
				return (NULL);
			return (ret);
		}
		all_free(split);
		i++;
	}
	return (NULL);
}
