/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:54 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/21 00:37:40 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_bundle *bundle)
{
	int n_option;

	if (bundle->token->next == NULL)
	{
		write(1, "\n", 1);
		return (SUCCESS);
	}
	n_option = 0;
	if (ft_strcmp(bundle->token->next->content, "-n") == 0) //strncmp 수정 
	{
		bundle->token = bundle->token->next;
		n_option = 1;
	}
	bundle->token = bundle->token->next;
	while (bundle->token && bundle->token->token_type != PIPE) //전체적으로 env 치환 기능 추가
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
