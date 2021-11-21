/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:40:42 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/21 17:33:19 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir_token(t_token *token)
{
	return (token->token_type >= REDIR_IN && token->token_type <= D_REDIR_OUT);
}

int	is_io_token(t_token *token)
{
	return (token->token_type >= REDIR_IN);
}

void	replace_env_token(t_token *temp, t_bundle *bundle)
{
	t_token	*delete_token;
	char	*env_tem;

	env_tem = ft_getenv(bundle, temp->content);
	free(temp->content);
	if (env_tem == NULL)
	{
		temp->pre->next = temp->next;
		delete_token = temp;
		temp = temp->pre;
		free(delete_token);
	}
	else
		temp->content = env_tem;
}
