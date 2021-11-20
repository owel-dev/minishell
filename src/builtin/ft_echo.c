/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:54 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/20 17:24:28 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_bundle *bundle)
{
	int n_option;

	// printf("hello\n");
	if (bundle == NULL)
		return (FAIL);
	if (bundle->token->next == NULL)
	{
		write(1, "\n", 1);
		return (SUCCESS);
	}
	n_option = 0;
	if (ft_strcmp(bundle->token->next->content, "-n") == 0)
	{
		bundle->token = bundle->token->next;
		n_option = 1;
	}
	bundle->token = bundle->token->next;
	while (bundle->token && bundle->token->token_type != PIPE)
	{
		write(1, bundle->token->content, ft_strlen(bundle->token->content));
		if (bundle->token->next)
			write(1, " ", 1);
		bundle->token = bundle->token->next;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
