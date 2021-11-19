/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:54 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/19 19:49:19 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_token *token)
{
	int n_option;

	if (token == NULL)
		return (FAIL);
	if (token->next == NULL)
	{
		write(1, "\n", 1);
		return (SUCCESS);
	}
	n_option = 0;
	if (ft_strcmp(token->next->content, "-n") == 0)
	{
		token = token->next;
		n_option = 1;
	}
	while (token)
	{
		write(1, token->content, ft_strlen(token->content));
		token = token->next;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
