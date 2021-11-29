/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:36:12 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/23 21:14:22 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s, int start)
{
	char	*result;
	int		len;

	len = ft_strlen(s) - start;
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	while (start < len)
	{
		result[start] = s[start];
		start++;
	}
	result[len] = 0;
	return (result);
}

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
		return (D_CLOSE);
	if (str == '\"' && preval == 0)
		return (D_OPEN);
	if (str == '\'' && preval == S_OPEN)
		return (S_CLOSE);
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

int	check_vaild_str(char *str, int start)
{
	if (check_quote(str, start, ft_strlen(str)) > 0)
		return (check_quote(str, start, ft_strlen(str)));
	if (str[start] == '|')
		return (PIPE);
	if (str[start] == '<' && str[start + 1] == '<')
		return (D_REDIR_IN);
	if (str[start] == '>' && str[start + 1] == '>')
		return (D_REDIR_OUT);
	if (str[start] == '<')
		return (REDIR_IN);
	if (str[start] == '>')
		return (REDIR_OUT);
	if (str[start] == '$')
	{
		if (str[start + 1] && str[start + 1] == '?')
			return (STATUS);
		return (ENV);
	}
	if (is_space(str[start + 1]) || ft_strchr("|<>$", str[start + 1]) ||
	check_quote(str, start + 1, ft_strlen(str)))
		return (1);
	return (0);
}
