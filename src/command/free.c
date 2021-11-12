/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:11:43 by ulee              #+#    #+#             */
/*   Updated: 2021/11/12 11:11:44 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_two(char **str)
{
	int i;

	if (str == NULL || *str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

char **dup_two(char **str)
{
	char **ret;
	int len;
	int i;

	if (str == NULL || *str == NULL)
		return (NULL);
	while (str[len])
		len++;
	ret = (char **)malloc(sizeof(char *) * len + 1);
	if (ret == NULL)
		return (NULL);
	ret[len] = NULL;
	i = 0;
	while (str[i])
	{
		ret[i] = ft_strdup(str[i]);
		if (ret[i] == NULL)
			return (NULL);
		i++;
	}
	return (ret);
}
