/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:54 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/21 14:55:09 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_bundle *bundle)
{
	int n_option;

	n_option = 0;
	while (bundle->token->next && bundle->token->token_type != PIPE) //전체적으로 env 치환 기능 추가
	{
		bundle->token = bundle->token->next;
		if (ft_strcmp(bundle->token->content, "-n") == 0) //strncmp 수정
		{
			n_option = 1;
			continue ;
		}
		if (bundle->token->next && bundle->token->redir >= REDIR_IN)
			redir_handler(bundle);
		if (bundle->token->token_type == 1)
			write(1, bundle->token->content, ft_strlen(bundle->token->content));
		if (bundle->token->next && bundle->token->back_space)
			write(1, " ", 1);
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
