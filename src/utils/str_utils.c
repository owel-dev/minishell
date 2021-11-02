/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:36:12 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/02 15:46:02 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_quote(char str, int preval)
{
	if (str == '\"' && preval == D_OPEN)
		return (0);
	if (str == '\"' && preval == 0)
		return (D_OPEN);
	if (str == '\'' && preval == S_OPEN)
		return (0);
	if (str == '\'' && preval == 0)
		return (S_OPEN);
	return (0);
}

int	check_priority(const char *str, int start)
{
	if ((str[start] == '&' && str[start + 1] == '&'))
		return (P_AND);
	if ((str[start] == '|' && str[start + 1] == '|'))
		return (P_OR);
	return (0);
}
